import sys
import numpy as np
from PyQt6.QtWidgets import QApplication, QWidget, QHBoxLayout, QVBoxLayout, QLabel, QComboBox, QLineEdit, QTextEdit, QPushButton, QListWidget
from PyQt6.QtGui import QPainter, QColor, QFont, QSyntaxHighlighter, QTextCharFormat
from PyQt6.QtCore import Qt, QRegularExpression
from PyQt6.QtWidgets import QMessageBox
from PyQt6.QtWidgets import QFileDialog
import json

from PyQt6.QtGui import QSyntaxHighlighter, QTextCharFormat, QFont, QColor
from PyQt6.QtCore import QRegularExpression

class CCodeHighlighter(QSyntaxHighlighter):
    def __init__(self, parent):
        super().__init__(parent)
        self.formats = {
            "keyword": self.create_format(QColor("#569CD6"), True),  # Niebieski (static, const)
            "type": self.create_format(QColor("#4EC9B0"), False),  # Zielony (typy danych)
            "function": self.create_format(QColor("#DCDCAA"), False),  # Żółty (nazwy funkcji)
            "macro": self.create_format(QColor("#C586C0"), True),  # Różowy (dyrektywy preprocesora)
            "number": self.create_format(QColor("#B5CEA8"), False),  # Oliwkowy (liczby)
            "operator": self.create_format(QColor("#D16969"), True)  # Czerwony (nawiasy, operatory)
        }

    def create_format(self, color, bold):
        fmt = QTextCharFormat()
        fmt.setForeground(color)
        if bold:
            fmt.setFontWeight(QFont.Weight.Bold)
        return fmt

    def highlightBlock(self, text):
        patterns = {
            "keyword": QRegularExpression(
                r"\b(auto|break|case|char|const|continue|default|do|double|else|enum|extern|float|for|goto|if|inline|int|long|register|restrict|return|short|signed|sizeof|static|struct|switch|typedef|union|unsigned|void|volatile|while)\b"
            ),
            "type": QRegularExpression(
                r"\b(uint8_t|uint16_t|uint32_t|uint64_t|int8_t|int16_t|int32_t|int64_t|size_t|ptrdiff_t)\b"
            ),
            "function": QRegularExpression(
                r"\b[a-zA-Z_][a-zA-Z0-9_]*(?=\()"
            ),
            "macro": QRegularExpression(
                r"#\s*(define|include|ifdef|ifndef|endif|pragma|error|warning)"
            ),
            "number": QRegularExpression(
                r"\b(0x[0-9A-Fa-f]+|\d+)\b"
            ),
            "operator": QRegularExpression(
                r"[\[\]{}=,;]"
            ),
        }

        for fmt_key, pattern in patterns.items():
            it = pattern.globalMatch(text)
            while it.hasNext():
                match = it.next()
                self.setFormat(match.capturedStart(), match.capturedLength(), self.formats[fmt_key])



class Char:
    def __init__(self, name, matrix):
        self.name = name
        self.matrix = matrix.copy()  # Zrobienie kopii macierzy


    def copy(self):
        # Tworzymy kopię macierzy i zwracamy nowy obiekt Char
        return Char(self.name, self.matrix.copy())

    def get_c_code(self):
        byte_array = []
        for row in self.matrix:
            byte_value = int("".join(map(str, row)), 2)
            byte_array.append(f"0x{byte_value:02X}")
        return f"static const uint8_t {self.name}[{len(self.matrix)}] = {{ " + ", ".join(byte_array) + " };"

    def update_pixel_matrix(self, new_matrix):
        # Uaktualnianie macierzy pikseli
        self.matrix = new_matrix

class LCDCharDesigner(QWidget):
    def __init__(self):
        super().__init__()
        self.standard_sizes = [(8, 5), (8, 6), (8, 7), (8, 8)]  # Standard sizes
        self.grid_size = (8, 5)  # Default size
        self.pixel_matrix = np.zeros(self.grid_size, dtype=int)
        self.characters = []  # Lista do przechowywania obiektów Char
        self.current_char_name = "char_data"  # Domyślny znak
        self.initUI()

    def initUI(self):
        self.setWindowTitle("LCD Character Designer")
        main_layout = QHBoxLayout()

        # Tworzymy widżet, który będzie zawierał left_layout
        left_widget = QWidget()
        left_layout = QVBoxLayout()
        
        # Dodajemy zawartość do left_layout
        self.size_selector = QComboBox()
        for size in self.standard_sizes:
            self.size_selector.addItem(f"{size[0]}x{size[1]}")
        self.size_selector.currentIndexChanged.connect(self.update_grid_size)
        left_layout.addWidget(QLabel("Select Grid Size:"))
        left_layout.addWidget(self.size_selector)
        
        self.char_name_input = QLineEdit()
        self.char_name_input.setPlaceholderText("Enter character name")
        self.char_name_input.textChanged.connect(self.update_c_code)
        left_layout.addWidget(QLabel("Character Name:"))
        left_layout.addWidget(self.char_name_input)
        
        # Używamy QHBoxLayout do wyśrodkowania siatki
        grid_layout = QHBoxLayout()
        self.pixel_grid = PixelGrid(self)
        grid_layout.addWidget(self.pixel_grid)
        grid_layout.setAlignment(self.pixel_grid, Qt.AlignmentFlag.AlignHCenter)
        left_layout.addLayout(grid_layout)
        
        # Przyciski do czyszczenia i zapisywania
        button_layout = QHBoxLayout()
        self.clear_button = QPushButton("Clear")
        self.clear_button.clicked.connect(self.clear_grid)
        self.save_button = QPushButton("Add to List")
        self.save_button.clicked.connect(self.save_char)

        button_layout.addWidget(self.clear_button)
        button_layout.addWidget(self.save_button)
        left_layout.addLayout(button_layout)
        
        # Lista zdefiniowanych znaków - przeniesiona poniżej przycisków
        self.char_list = QListWidget()
        self.char_list.itemClicked.connect(self.load_selected_char)
        left_layout.addWidget(QLabel("Defined Characters:"))
        left_layout.addWidget(self.char_list)

        self.code_view = QTextEdit()
        self.code_view.setFont(QFont("Courier", 12, QFont.Weight.Bold))
        self.code_view.setReadOnly(True)
        self.code_view.setStyleSheet("background-color: #282c34; color: #abb2bf; padding: 5px;")
        self.code_view.setMinimumWidth(750)  # Minimalna szerokość dla okna z kodem
        self.code_view.setMinimumHeight(100)  # Minimalna wysokość
        self.highlighter = CCodeHighlighter(self.code_view.document())
        
        # Ustawiamy left_layout w left_widget
        left_widget.setLayout(left_layout)

        # Ustawiamy stałą szerokość dla left_widget
        left_widget.setFixedWidth(280)

        right_layout = QVBoxLayout()
        right_layout.addWidget(QLabel("Generated C Code:"))
        right_layout.addWidget(self.code_view, stretch=1)
        right_layout.setStretchFactor(self.code_view, 1)
        
        # Dodajemy left_widget do main_layout
        main_layout.addWidget(left_widget, stretch=1)
        main_layout.addLayout(right_layout, stretch=2)
        self.setLayout(main_layout)
        self.update_c_code()

        # Przycisk operacji na liscie
        button_layout3 = QHBoxLayout();
        self.delete_button = QPushButton("Remove Selected from List")
        self.delete_button.clicked.connect(self.delete_selected_char)

        button_layout3.addWidget(self.delete_button)

        # Dodajemy do głównego layoutu
        left_layout.addLayout(button_layout3)

        # Przyciski pod listą
        button_layout2 = QHBoxLayout()

        self.save_list_button = QPushButton("Save List")
        self.save_list_button.clicked.connect(self.save_list_to_file)

        self.load_list_button = QPushButton("Load List")
        self.load_list_button.clicked.connect(self.load_list_from_file)

        self.clear_list_button = QPushButton("Delete list")
        self.clear_list_button.clicked.connect(self.clear_all_chars)

        button_layout2.addWidget(self.save_list_button)
        button_layout2.addWidget(self.load_list_button)
        button_layout2.addWidget(self.clear_list_button)

        # Dodajemy do głównego layoutu
        left_layout.addLayout(button_layout2)


    def update_grid_size(self):
        if len(self.characters) > 0:
            # Jeśli lista zawiera elementy, zablokuj zmianę rozmiaru
            self.size_selector.setEnabled(False)
            # Możesz dodać jakiś komunikat, jeśli chcesz informować użytkownika
            self.show_message("You cannot change the grid size once a character is defined.")
            return
        else:
            # Jeśli lista jest pusta, umożliwiamy zmianę rozmiaru
            self.size_selector.setEnabled(True)
            index = self.size_selector.currentIndex()
            self.grid_size = self.standard_sizes[index]
            self.pixel_matrix = np.zeros(self.grid_size, dtype=int)
            self.pixel_grid.update_grid_size()  # Aktualizujemy rozmiar grida
            self.update_c_code()


    def show_message(self, message):
        msg = QMessageBox()
        msg.setIcon(QMessageBox.Icon.Information)  # Typ okna dialogowego (informacyjne)
        msg.setText(message)  # Ustawienie tekstu komunikatu
        msg.setWindowTitle("Information")  # Tytuł okna
        msg.setStandardButtons(QMessageBox.StandardButton.Ok)  # Przycisk OK
        msg.exec()  # Wywołanie okna komunikatu

    def toggle_pixel(self, x, y):
        # Konwertujemy x i y na liczby całkowite, aby zapobiec błędowi typu
        x = int(x)
        y = int(y)

        if 0 <= y < self.grid_size[0] and 0 <= x < self.grid_size[1]:
            self.pixel_matrix[y, x] ^= 1


    def update_c_code(self):
        # Tylko zdefiniowane znaki w characters
        c_code = self.generate_c_code()
        self.code_view.setText(c_code)
        self.adjust_code_view_width()
        self.adjustSize()

    def generate_c_code(self):
        c_code = ""
        max_line_length = 0  # Zmienna do określania długości najdłuższej definicji

        # Iterujemy po elementach w liście self.characters
        for char in self.characters:
            char_code = char.get_c_code()
            c_code += char_code + "\n"
            
            max_line_length = max(max_line_length, len(char_code))

        self.max_code_width = max_line_length  # Ustawiamy szerokość kodu na najdłuższą linię
        return c_code
    
    def adjust_code_view_width(self):
        text_length = self.max_code_width
        min_width = 750
        calculated_width = 10 * text_length + 50
        new_width = max(min_width, calculated_width)
        
        self.code_view.setFixedWidth(new_width)

    
    def clear_grid(self):
        self.pixel_matrix = np.zeros(self.grid_size, dtype=int)
        self.pixel_grid.update()
    
    def save_char(self):
        char_name = self.char_name_input.text().strip()
        
        # Sprawdzamy, czy nazwa zaczyna się od cyfry
        if char_name and char_name[0].isdigit():
            self.show_message("Character name cannot start with a digit.")
            return  # Zatrzymaj dalsze wykonywanie, jeśli nazwa zaczyna się od cyfry
        
        if char_name:
            self.current_char_name = char_name

            # Sprawdzamy, czy taki znak już istnieje w bazie
            existing_char = next((char for char in self.characters if char.name == char_name), None)
            
            if existing_char:
                # Jeśli znak już istnieje, zaktualizuj go
                existing_char.matrix = self.pixel_matrix
            else:
                # Jeśli znak nie istnieje, stwórz nowy obiekt Char i dodaj go do listy
                new_char = Char(self.current_char_name, self.pixel_matrix)
                self.characters.append(new_char)
            
            # Aktualizujemy listę na UI
            self.char_list.clear()
            for char in self.characters:
                self.char_list.addItem(char.name)
            
            self.update_c_code()  # Zaktualizuj kod po zapisaniu
        
    def load_selected_char(self, item):
        char_name = item.text()
        
        # Szukamy obiektu Char w bazie po nazwie
        char = next((char for char in self.characters if char.name == char_name), None)
        
        if char:
            self.current_char_name = char.name
            self.pixel_matrix = char.matrix  # Ładujemy macierz znaku
            self.pixel_grid.update()
            self.char_name_input.setText(self.current_char_name)
            self.update_c_code()

    def save_list_to_file(self):
        # Otwórz okno dialogowe, aby wybrać lokalizację zapisu
        filename, _ = QFileDialog.getSaveFileName(self, "Save Character List", "", "JSON Files (*.json);;All Files (*)")
        
        if filename:
            # Jeśli użytkownik nie podał rozszerzenia .json, dodaj je automatycznie
            if not filename.lower().endswith(".json"):
                filename += ".json"
            
            with open(filename, 'w') as f:
                # Przygotowujemy dane do zapisania (nazwy i macierze)
                data = [{"name": char.name, "matrix": char.matrix.tolist()} for char in self.characters]
                json.dump(data, f, indent=4)
            
            self.show_message(f"List of characters saved to {filename}")
        else:
            self.show_message("Save operation was canceled.")


    def load_list_from_file(self):
        # Otwórz okno dialogowe, aby wybrać plik do wczytania
        filename, _ = QFileDialog.getOpenFileName(self, "Open Character List", "", "JSON Files (*.json);;All Files (*)")
        
        if filename:
            try:
                with open(filename, 'r') as f:
                    data = json.load(f)
                    
                    # Wczytanie danych z pliku i tworzenie obiektów Char
                    self.characters = []
                    for item in data:
                        name = item['name']
                        matrix = np.array(item['matrix'])
                        self.characters.append(Char(name, matrix))
                    
                    # Zaktualizuj listę na UI
                    self.char_list.clear()
                    for char in self.characters:
                        self.char_list.addItem(char.name)
                    
                    self.update_c_code()
                    self.show_message(f"List of characters loaded from {filename}")
            
            except json.JSONDecodeError:
                self.show_message(f"Error reading {filename}. The file may not be in the correct format.")
            except Exception as e:
                self.show_message(f"Error loading file: {e}")
        else:
            self.show_message("Open operation was canceled.")


    def delete_selected_char(self):
        # Pobieramy zaznaczony element z listy
        selected_item = self.char_list.currentItem()
        if selected_item:
            char_name = selected_item.text()
            
            # Szukamy obiektu Char w bazie
            char = next((char for char in self.characters if char.name == char_name), None)
            
            if char:
                # Usuwamy obiekt z listy
                self.characters.remove(char)
                # Usuwamy item z listy w UI
                self.char_list.takeItem(self.char_list.row(selected_item))
                self.update_c_code()
                # self.show_message(f"Character '{char_name}' deleted.")

    def clear_all_chars(self):
        # Usuwamy wszystkie elementy z listy
        self.characters.clear()
        # Wyczyść także widok na liście
        self.char_list.clear()
        # Zaktualizuj kod, ponieważ lista znaków została opróżniona
        self.update_c_code()


class PixelGrid(QWidget):
    def __init__(self, parent):
        super().__init__(parent)
        self.parent = parent
        self.pixel_width = 20
        self.pixel_height = 25
        self.update_grid_size()

    def update_grid_size(self):
        grid_width = self.parent.grid_size[1]
        grid_height = self.parent.grid_size[0]
        self.setFixedSize(self.pixel_width * grid_width, self.pixel_height * grid_height)

    def paintEvent(self, event):
        painter = QPainter(self)
        grid_width = self.parent.grid_size[1]
        grid_height = self.parent.grid_size[0]
        cell_width = self.pixel_width
        cell_height = self.pixel_height
        
        for y in range(grid_height):
            for x in range(grid_width):
                rect_x, rect_y = x * cell_width, y * cell_height
                color = QColor(0, 0, 0) if self.parent.pixel_matrix[y, x] else QColor(173, 255, 47)
                painter.fillRect(rect_x, rect_y, cell_width - 2, cell_height - 2, color)

    def mousePressEvent(self, event):
        x = int(event.position().x()) // self.pixel_width
        y = int(event.position().y()) // self.pixel_height
        
        # Upewnijmy się, że x i y są w zakresie
        if 0 <= x < self.parent.grid_size[1] and 0 <= y < self.parent.grid_size[0]:
            self.parent.toggle_pixel(x, y)
            self.update()


if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = LCDCharDesigner()
    window.show()
    sys.exit(app.exec())
