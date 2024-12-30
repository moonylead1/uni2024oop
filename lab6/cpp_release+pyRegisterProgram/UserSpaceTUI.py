from textual.app import App, ComposeResult
from textual.containers import Container
from textual.widgets import Button, Header, Footer, Input, Static, DataTable  # DataTable needs directly from widgets
from textual.screen import Screen
from textual import on
import json
import os
from UserSpace import UserManager

class LoginScreen(Screen):
    def compose(self) -> ComposeResult:
        yield Container(
            Header(show_clock=True),
            Static("Login to System", classes="title"),
            Input(placeholder="Enter email", id="email_input"),
            Button("Login", variant="primary", id="login_btn"),
            Button("Register New User", variant="default", id="goto_register_btn"),
            Static("", id="message"),
            id="login_container"
        )

    @on(Button.Pressed, "#login_btn")
    def handle_login(self):
        email = self.query_one("#email_input").value
        success, message = self.app.user_manager.login(email)
        self.query_one("#message").update(f"{'✓' if success else '✗'} {message}")
        if success:
            self.app.push_screen("users")

    @on(Button.Pressed, "#goto_register_btn")
    def goto_register(self):
        self.app.push_screen("register")

class RegisterScreen(Screen):
    def compose(self) -> ComposeResult:
        yield Container(
            Header(show_clock=True),
            Static("Register New User", classes="title"),
            Input(placeholder="User ID", id="id_input"),
            Input(placeholder="Name", id="name_input"),
            Input(placeholder="Email", id="email_input"),
            Input(placeholder="Role", id="role_input"),
            Button("Register", variant="primary", id="register_btn"),
            Button("Back to Login", variant="default", id="back_btn"),
            Static("", id="message"),
            id="register_container"
        )

    @on(Button.Pressed, "#register_btn")
    def handle_register(self):
        user_id = self.query_one("#id_input").value
        name = self.query_one("#name_input").value
        email = self.query_one("#email_input").value
        role = self.query_one("#role_input").value or "user"

        success, message = self.app.user_manager.register(user_id, name, email, role)
        self.query_one("#message").update(f"{'✓' if success else '✗'} {message}")
        if success:
            self.app.push_screen("users")

    @on(Button.Pressed, "#back_btn")
    def go_back(self):
        self.app.pop_screen()

class UsersScreen(Screen):
    BINDINGS = [
        ("space", "toggle_row", "Toggle Selection"),
    ]
    
    def __init__(self):
        super().__init__()
        self.selected_row_key = None

    def compose(self) -> ComposeResult:
        yield Container(
            Header(show_clock=True),
            Static("User Management", classes="title"),
            Static("Use SPACE to select/deselect a row", classes="help-text"),
            DataTable(id="users_table"),
            Button("Logout Selected", variant="error", id="logout_btn"),
            Button("Back to Login", variant="default", id="back_btn"),
            Static("", id="message"),
            id="users_container"
        )

    def on_mount(self):
        table = self.query_one("#users_table")
        table.cursor_type = "row"
        table.add_columns("Select", "ID", "Name", "Email", "Role", "Status")
        self.refresh_users()

    def refresh_users(self):
        table = self.query_one("#users_table")
        table.clear()
        for user in self.app.user_manager.users:  # directly iterating over the list
            select_mark = "✓" if user["email"] == self.selected_row_key else " "
            table.add_row(
                select_mark,
                user["id"],
                user["name"],
                user["email"],
                user["role"],
                user["status"]
            )

    def action_toggle_row(self):
        table = self.query_one("#users_table")
        if table.cursor_row is not None:
            try:
                row = table.get_row_at(table.cursor_row)
                email = row[3]  # Email is now at index 3 due to added Select column
                
                if self.selected_row_key == email:
                    self.selected_row_key = None
                else:
                    self.selected_row_key = email
                
                self.refresh_users()
            except IndexError:
                self.query_one("#message").update("✗ Please select a valid row")

    @on(Button.Pressed, "#logout_btn")
    def handle_logout(self):
        if self.selected_row_key is None:
            self.query_one("#message").update("✗ Please select a user first")
            return
            
        success, message = self.app.user_manager.logout(self.selected_row_key)
        self.query_one("#message").update(f"{'✓' if success else '✗'} {message}")
        if success:
            self.selected_row_key = None
        self.refresh_users()

    @on(Button.Pressed, "#back_btn")
    def go_back(self):
        self.app.pop_screen()

class UserManagementApp(App):
    CSS = """
    .title {
        dock: top;
        padding: 1;
        width: 100%;
        text-align: center;
        text-style: bold;
    }

    .help-text {
        text-align: center;
        color: $text-disabled;
    }

    #login_container, #register_container, #users_container {
        width: 80%;
        height: 100%;
        align: center middle;
    }

    Input {
        margin: 1;
    }

    Button {
        margin: 1;
    }

    #message {
        height: 1;
        content-align: center middle;
        text-style: italic;
    }

    DataTable {
        height: 50%;
        margin: 1;
    }
    """

    SCREENS = {
        "login": LoginScreen,
        "register": RegisterScreen,
        "users": UsersScreen,
    }

    def __init__(self):
        super().__init__()
        self.user_manager = UserManager()

    def on_mount(self) -> None:
        self.push_screen("login")

if __name__ == "__main__":
    app = UserManagementApp()
    app.run()