import sys
import numpy as np
from PyQt6.QtWidgets import (
    QApplication, QWidget, QHBoxLayout, QVBoxLayout, QLabel, QComboBox, QLineEdit, QTextEdit, QPushButton, QListWidget,
    QMessageBox, QFileDialog, QInputDialog
)
from PyQt6.QtGui import QPainter, QColor, QFont, QSyntaxHighlighter, QTextCharFormat
from PyQt6.QtCore import Qt, QRegularExpression
import json

class CCodeHighlighter(QSyntaxHighlighter):
    def __init__(self, parent):
        super().__init__(parent)
        self.formats = {
            "keyword": self.create_format(QColor("#569CD6"), True),
            "type": self.create_format(QColor("#4EC9B0"), False),
            "function": self.create_format(QColor("#DCDCAA"), False),
            "macro": self.create_format(QColor("#C586C0"), True),
            "number": self.create_format(QColor("#B5CEA8"), False),
            "operator": self.create_format(QColor("#D16969"), True)
        }

    def create_format(self, color, bold):
        fmt = QTextCharFormat()
        fmt.setForeground(color)
        if bold:
            fmt.setFontWeight(QFont.Weight.Bold)
        return fmt

    def highlightBlock(self, text):
        patterns = {
            "keyword": QRegularExpression(r"\b(auto|break|case|char|const|continue|default|do|double|else|enum|extern|float|for|goto|if|inline|int|long|register|restrict|return|short|signed|sizeof|static|struct|switch|typedef|union|unsigned|void|volatile|while)\b"),
            "type": QRegularExpression(r"\b(uint8_t|uint16_t|uint32_t|uint64_t|int8_t|int16_t|int32_t|int64_t|size_t|ptrdiff_t)\b"),
            "function": QRegularExpression(r"\b[a-zA-Z_][a-zA-Z0-9_]*(?=\()"),
            "macro": QRegularExpression(r"#\s*(define|include|ifdef|ifndef|endif|pragma|error|warning)"),
            "number": QRegularExpression(r"\b(0x[0-9A-Fa-f]+|\d+)\b"),
            "operator": QRegularExpression(r"[\[\]{}=,;]"),
        }

        for fmt_key, pattern in patterns.items():
            it = pattern.globalMatch(text)
            while it.hasNext():
                match = it.next()
                self.setFormat(match.capturedStart(), match.capturedLength(), self.formats[fmt_key])

class Char:
    def __init__(self, name, matrix):
        self.name = name
        self.matrix = matrix.copy()

    def copy(self):
        return Char(self.name, self.matrix.copy())

    def get_c_code(self):
        byte_array = [f"0x{int(''.join(map(str, row)), 2):02X}" for row in self.matrix]
        return f"static const uint8_t {self.name}[{len(self.matrix)}] = {{ " + ", ".join(byte_array) + " };"

class LCDCharDesigner(QWidget):
    def __init__(self):
        super().__init__()
        self.standard_sizes = [(8, 5), (8, 6), (8, 7), (8, 8)]
        self.grid_size = (8, 5)
        self.pixel_matrix = np.zeros(self.grid_size, dtype=int)
        self.characters = []
        self.current_char_name = "char_data"
        self.banks = {}
        self.initUI()

    def initUI(self):
        self.setWindowTitle("LCD Character Designer")
        main_layout = QHBoxLayout()

        banks_layout = self.create_banks_layout()
        main_layout.addLayout(banks_layout)

        left_widget = QWidget()
        left_layout = QVBoxLayout()
        self.setup_left_layout(left_layout)
        left_widget.setLayout(left_layout)
        left_widget.setFixedWidth(280)

        right_layout = QVBoxLayout()
        self.setup_right_layout(right_layout)

        main_layout.addWidget(left_widget, stretch=1)
        main_layout.addLayout(right_layout, stretch=2)
        self.setLayout(main_layout)
        self.update_c_code()

    def create_banks_layout(self):
        banks_layout = QVBoxLayout()
        self.bank_list = QListWidget()
        self.bank_list.itemClicked.connect(self.load_bank_chars)
        banks_layout.addWidget(QLabel("Character Banks:"))
        banks_layout.addWidget(self.bank_list)

        self.bank_chars_list = QListWidget()
        banks_layout.addWidget(QLabel("Characters in Bank:"))
        banks_layout.addWidget(self.bank_chars_list)

        btn_layout = QHBoxLayout()
        self.add_bank_button = QPushButton("Add Bank")
        self.add_bank_button.clicked.connect(self.add_bank)
        self.delete_bank_button = QPushButton("Delete Bank")
        self.delete_bank_button.clicked.connect(self.delete_bank)
        btn_layout.addWidget(self.add_bank_button)
        btn_layout.addWidget(self.delete_bank_button)
        banks_layout.addLayout(btn_layout)

        self.add_char_to_bank_button = QPushButton("Add Selected Char to Bank")
        self.add_char_to_bank_button.clicked.connect(self.add_char_to_bank)
        banks_layout.addWidget(self.add_char_to_bank_button)

        return banks_layout

    def setup_left_layout(self, left_layout):
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

        grid_layout = QHBoxLayout()
        self.pixel_grid = PixelGrid(self)
        grid_layout.addWidget(self.pixel_grid)
        grid_layout.setAlignment(self.pixel_grid, Qt.AlignmentFlag.AlignHCenter)
        left_layout.addLayout(grid_layout)

        button_layout = QHBoxLayout()
        self.clear_button = QPushButton("Clear")
        self.clear_button.clicked.connect(self.clear_grid)
        self.save_button = QPushButton("Add to Def Char")
        self.save_button.clicked.connect(self.save_char)
        button_layout.addWidget(self.clear_button)
        button_layout.addWidget(self.save_button)
        left_layout.addLayout(button_layout)

        self.char_list = QListWidget()
        self.char_list.itemClicked.connect(self.load_selected_char)
        left_layout.addWidget(QLabel("Defined Characters:"))
        left_layout.addWidget(self.char_list)

        button_layout3 = QHBoxLayout()
        self.delete_button = QPushButton("Remove Selected Char from List")
        self.delete_button.clicked.connect(self.delete_selected_char)
        button_layout3.addWidget(self.delete_button)
        left_layout.addLayout(button_layout3)

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
        left_layout.addLayout(button_layout2)

    def setup_right_layout(self, right_layout):
        self.code_view = QTextEdit()
        self.code_view.setFont(QFont("Courier", 12, QFont.Weight.Bold))
        self.code_view.setReadOnly(True)
        self.code_view.setStyleSheet("background-color: #282c34; color: #abb2bf; padding: 5px;")
        self.code_view.setMinimumWidth(750)
        self.code_view.setMinimumHeight(100)
        self.highlighter = CCodeHighlighter(self.code_view.document())
        right_layout.addWidget(QLabel("Generated C Code:"))
        right_layout.addWidget(self.code_view, stretch=1)
        right_layout.setStretchFactor(self.code_view, 1)

    def update_grid_size(self):
        if len(self.characters) > 0:
            self.size_selector.setEnabled(False)
            self.show_message("You cannot change the grid size once a character is defined.")
            return
        else:
            self.size_selector.setEnabled(True)
            index = self.size_selector.currentIndex()
            self.grid_size = self.standard_sizes[index]
            self.pixel_matrix = np.zeros(self.grid_size, dtype=int)
            self.pixel_grid.update_grid_size()
            self.update_c_code()

    def show_message(self, message):
        msg = QMessageBox()
        msg.setIcon(QMessageBox.Icon.Information)
        msg.setText(message)
        msg.setWindowTitle("Information")
        msg.setStandardButtons(QMessageBox.StandardButton.Ok)
        msg.exec()

    def toggle_pixel(self, x, y):
        x = int(x)
        y = int(y)
        if 0 <= y < self.grid_size[0] and 0 <= x < self.grid_size[1]:
            self.pixel_matrix[y, x] ^= 1
            self.save_char()

    def update_c_code(self):
        c_code = self.generate_c_code()
        c_code += "\n"
        c_code += self.generate_char_bank_c_code()
        self.code_view.setText(c_code)
        self.adjust_code_view_width()
        self.adjustSize()

    def generate_c_code(self):
        c_code = ""
        max_line_length = 0
        for char in self.characters:
            char_code = char.get_c_code()
            c_code += char_code + "\n"
            max_line_length = max(max_line_length, len(char_code))
        self.max_code_width = max_line_length
        return c_code
    
    def generate_char_bank_c_code(self):
        char_bank_c_code = ""
        if self.bank_list.count() > 0:
            for i in range(self.bank_list.count()):  
                bank_name_item= self.bank_list.item(i)
                bank_name= bank_name_item.text()
                char_bank_c_code += "static const char_bank_struct_t " + bank_name + " = {\n"
                for char in self.banks[bank_name]:
                    char_bank_c_code += char + ",\n"
                char_bank_c_code += "};\n"
                char_bank_c_code += "\n"
                char_bank_c_code += "enum " + bank_name +"_e \n{\n"
                for char in self.banks[bank_name]:
                    if char[0].islower():
                        new_char = char[0].upper() + char[1:]  # Zamień na dużą
                    elif char[0].isupper():
                        new_char = char[0].lower() + char[1:]  # Zamień na małą
                    
                    char_bank_c_code += new_char + ",\n"
                char_bank_c_code += "};\n"
                char_bank_c_code += "\n"

                # self.banks[bank_name_item]

        return char_bank_c_code

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
        if char_name and char_name[0].isdigit():
            self.show_message("Character name cannot start with a digit.")
            return
        if char_name:
            self.current_char_name = char_name
            existing_char = next((char for char in self.characters if char.name == char_name), None)
            if existing_char:
                existing_char.matrix = self.pixel_matrix.copy()
            else:
                new_char = Char(self.current_char_name, self.pixel_matrix)
                self.characters.append(new_char)
            self.update_char_list()
            self.update_c_code()

    def update_char_list(self):
        self.char_list.clear()
        for char in self.characters:
            self.char_list.addItem(char.name)

    def load_selected_char(self, item):
        char_name = item.text()
        char = next((char for char in self.characters if char.name == char_name), None)
        if char:
            self.current_char_name = char.name
            self.pixel_matrix = char.matrix
            self.pixel_grid.update()
            self.char_name_input.setText(self.current_char_name)
            self.update_c_code()

    def save_list_to_file(self):
        filename, _ = QFileDialog.getSaveFileName(self, "Save Character List", "", "JSON Files (*.json);;All Files (*)")
        if filename:
            if not filename.lower().endswith(".json"):
                filename += ".json"
            try:
                with open(filename, 'w') as f:
                    data = {
                        "characters": [{"name": char.name, "matrix": char.matrix.tolist()} for char in self.characters],
                        "banks": {bank_name: bank_chars for bank_name, bank_chars in self.banks.items()}
                    }
                    json.dump(data, f, indent=4)
                self.show_message(f"List of characters and banks saved to {filename}")
            except Exception as e:
                self.show_message(f"Error saving file: {e}")
        else:
            self.show_message("Save operation was canceled.")

    def load_list_from_file(self):
        filename, _ = QFileDialog.getOpenFileName(self, "Open Character List", "", "JSON Files (*.json);;All Files (*)")
        if filename:
            try:
                with open(filename, 'r') as f:
                    data = json.load(f)
                    self.characters = [Char(item['name'], np.array(item['matrix'])) for item in data.get("characters", [])]
                    self.banks = {bank_name: bank_chars for bank_name, bank_chars in data.get("banks", {}).items()}
                    self.update_char_list()
                    self.update_banks_list()
                    self.update_bank_view()
                    self.update_c_code()
                    self.show_message(f"List of characters and banks loaded from {filename}")
            except json.JSONDecodeError:
                self.show_message(f"Error reading {filename}. The file may not be in the correct format.")
            except Exception as e:
                self.show_message(f"Error loading file: {e}")
        else:
            self.show_message("Open operation was canceled.")

    def delete_selected_char(self):
        selected_item = self.char_list.currentItem()
        if selected_item:
            char_name = selected_item.text()
            char = next((char for char in self.characters if char.name == char_name), None)
            if char:
                self.characters.remove(char)
                self.char_list.takeItem(self.char_list.row(selected_item))
                self.remove_char_from_banks(char_name)
                self.update_bank_view()
                self.update_c_code()

    def clear_all_chars(self):
        for bank in self.banks.values():
            bank.clear()
        self.update_bank_view()
        self.characters.clear()
        self.char_list.clear()
        self.update_c_code()
        self.show_message("All characters deleted from char list and banks.")

    def add_bank(self):
        bank_name, ok = QInputDialog.getText(self, "New Bank", "Enter bank name:")
        if ok and bank_name.strip():
            if bank_name in self.banks:
                self.show_message("Bank already exists!")
            else:
                self.banks[bank_name] = []
                self.bank_list.addItem(bank_name)
        self.update_c_code()

    def delete_bank(self):
        selected_item = self.bank_list.currentItem()
        if selected_item:
            bank_name = selected_item.text()
            del self.banks[bank_name]
            self.bank_list.takeItem(self.bank_list.row(selected_item))
            self.bank_chars_list.clear()
        self.update_c_code()

    def add_char_to_bank(self):
        selected_char_item = self.char_list.currentItem()
        selected_bank_item = self.bank_list.currentItem()
        if selected_char_item and selected_bank_item:
            char_name = selected_char_item.text()
            bank_name = selected_bank_item.text()
            if char_name not in self.banks[bank_name]:
                if len(self.banks[bank_name]) < 8:
                    self.banks[bank_name].append(char_name)
                    self.bank_chars_list.addItem(char_name)
                else:
                    self.show_message("Bank is full (max 8 characters).")

    def remove_char_from_banks(self, char_name):
        for bank_name, chars in self.banks.items():
            if char_name in chars:
                self.banks[bank_name].remove(char_name)

    def load_bank_chars(self, item):
        bank_name = item.text()
        self.bank_chars_list.clear()
        for char in self.banks[bank_name]:
            self.bank_chars_list.addItem(char)

    def update_banks_list(self):
        self.bank_list.clear()
        for bank_name in self.banks.keys():
            self.bank_list.addItem(bank_name)
        self.update_c_code()

    def update_bank_view(self):
        selected_bank_item = self.bank_list.currentItem()
        if selected_bank_item:
            bank_name = selected_bank_item.text()
            self.bank_chars_list.clear()
            for char_name in self.banks.get(bank_name, []):
                self.bank_chars_list.addItem(char_name)
        else:
            self.bank_chars_list.clear()

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
        if 0 <= x < self.parent.grid_size[1] and 0 <= y < self.parent.grid_size[0]:
            self.parent.toggle_pixel(x, y)
            self.update()

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = LCDCharDesigner()
    window.show()
    sys.exit(app.exec())