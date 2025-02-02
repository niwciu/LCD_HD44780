import sys
import numpy as np
from PyQt6.QtWidgets import QApplication, QWidget, QHBoxLayout, QVBoxLayout, QLabel, QComboBox, QLineEdit, QTextEdit, QPushButton, QListWidget
from PyQt6.QtGui import QPainter, QColor, QFont, QSyntaxHighlighter, QTextCharFormat
from PyQt6.QtCore import Qt, QRegularExpression

class CCodeHighlighter(QSyntaxHighlighter):
    def __init__(self, parent):
        super().__init__(parent)
        self.formats = {
            "keyword": self.create_format(Qt.GlobalColor.cyan, True),
            "number": self.create_format(Qt.GlobalColor.yellow, True),
            "variable": self.create_format(Qt.GlobalColor.green, False),
            "brackets": self.create_format(Qt.GlobalColor.red, True)
        }
    
    def create_format(self, color, bold):
        fmt = QTextCharFormat()
        fmt.setForeground(color)
        if bold:
            fmt.setFontWeight(QFont.Weight.Bold)
        return fmt
    
    def highlightBlock(self, text):
        patterns = {
            "keyword": QRegularExpression(r"\buint8_t\b"),
            "number": QRegularExpression(r"0x[0-9A-Fa-f]+"),
            "variable": QRegularExpression(r"\b[a-zA-Z_][a-zA-Z0-9_]*\b"),
            "brackets": QRegularExpression(r"[{}]"),
        }
        
        for fmt_key, pattern in patterns.items():
            it = pattern.globalMatch(text)
            while it.hasNext():
                match = it.next()
                self.setFormat(match.capturedStart(), match.capturedLength(), self.formats[fmt_key])

class LCDCharDesigner(QWidget):
    def __init__(self):
        super().__init__()
        self.standard_sizes = [(8, 5), (8, 6), (8, 7), (8, 8)]  # Standard sizes
        self.grid_size = (8, 5)  # Default size
        self.pixel_matrix = np.zeros(self.grid_size, dtype=int)
        self.characters = {}  # Zmienna do przechowywania wielu znaków
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
        self.save_button = QPushButton("Save")
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
        self.code_view.setMinimumWidth(350)  # Minimalna szerokość dla okna z kodem
        self.code_view.setMinimumHeight(100)  # Minimalna wysokość
        self.highlighter = CCodeHighlighter(self.code_view.document())
        
        # Ustawiamy left_layout w left_widget
        left_widget.setLayout(left_layout)

        # Ustawiamy stałą szerokość dla left_widget
        left_widget.setFixedWidth(250)

        right_layout = QVBoxLayout()
        right_layout.addWidget(QLabel("Generated C Code:"))
        right_layout.addWidget(self.code_view, stretch=1)
        right_layout.setStretchFactor(self.code_view, 1)
        
        # Dodajemy left_widget do main_layout
        main_layout.addWidget(left_widget, stretch=1)
        main_layout.addLayout(right_layout, stretch=2)
        self.setLayout(main_layout)
        self.update_c_code()

    def update_grid_size(self):
        index = self.size_selector.currentIndex()
        self.grid_size = self.standard_sizes[index]
        self.pixel_matrix = np.zeros(self.grid_size, dtype=int)
        self.pixel_grid.update_grid_size()  # Aktualizujemy rozmiar grida
        self.update_c_code()

    def toggle_pixel(self, x, y):
        if 0 <= y < self.grid_size[0] and 0 <= x < self.grid_size[1]:
            self.pixel_matrix[y, x] ^= 1
            self.update_c_code()
    
    def update_c_code(self):
        # Tylko zdefiniowane znaki w characters
        c_code = self.generate_c_code()
        self.code_view.setText(c_code)
        self.adjust_code_view_width()

    def generate_c_code(self):
        c_code = ""
        max_line_length = 0  # Zmienna do określania długości najdłuższej definicji

        for idx, (name, matrix) in enumerate(self.characters.items()):
            byte_array = []
            for row in matrix:
                byte_value = int("".join(map(str, row)), 2)
                byte_array.append(f"0x{byte_value:02X}")
            char_code = f"uint8_t {name}[{self.grid_size[0]}] = {{ " + ", ".join(byte_array) + " };"
            if idx < len(self.characters) - 1:
                c_code += char_code + "\n"
            else:
                c_code += char_code

            max_line_length = max(max_line_length, len(char_code))

        self.max_code_width = max_line_length  # Ustawiamy szerokość kodu na najdłuższą linię
        return c_code
    
    def adjust_code_view_width(self):
        text_length = self.max_code_width
        min_width = 350
        calculated_width = 10 * text_length + 50
        new_width = max(min_width, calculated_width)
        self.code_view.setFixedWidth(new_width)
    
    def clear_grid(self):
        self.pixel_matrix = np.zeros(self.grid_size, dtype=int)
        self.pixel_grid.update()
        self.update_c_code()
    
    def save_char(self):
        char_name = self.char_name_input.text().strip()
        if char_name:
            self.current_char_name = char_name
            self.characters[self.current_char_name] = self.pixel_matrix
            self.char_list.addItem(char_name)  # Dodajemy do listy nazw
            self.update_c_code()  # Zaktualizuj kod po zapisaniu
    
    def load_selected_char(self, item):
        # Ładujemy wybrany znak
        self.current_char_name = item.text()
        self.pixel_matrix = self.characters.get(self.current_char_name, np.zeros(self.grid_size, dtype=int))
        self.pixel_grid.update()
        self.char_name_input.setText(self.current_char_name)
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
        grid_width = self.parent.grid_size[1]
        grid_height = self.parent.grid_size[0]
        cell_width = self.pixel_width
        cell_height = self.pixel_height
        x, y = event.pos().x() // cell_width, event.pos().y() // cell_height
        if 0 <= x < grid_width and 0 <= y < grid_height:
            self.parent.toggle_pixel(x, y)
            self.update()

if __name__ == '__main__':
    app = QApplication(sys.argv)
    designer = LCDCharDesigner()
    designer.show()
    sys.exit(app.exec())
