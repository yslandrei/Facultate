package org.example.javafx;


import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Modality;
import javafx.stage.Stage;
import org.example.domain.*;
import org.example.service.*;

public class LogInSignUpController {
     @FXML
     private TextField textFieldUsernameLogIn;
    @FXML
    private PasswordField passwordFieldPasswordLogIn;
    @FXML
    private Button buttonLogIn;
    @FXML
    private TextField textFieldFirstNameSignUp;
    @FXML
    private TextField textFieldLastNameSignUp;
    @FXML
    private TextField textFieldUsernameSignUp;
    @FXML
    private TextField passwordFieldPasswordSignUp;
    @FXML
    private Button buttonSignUp;

    private UserService userService;

    private ConcertService concertService;

    private TicketService ticketService;

    public void setService(UserService userService, ConcertService concertService, TicketService ticketService) {
        this.userService = userService;
        this.concertService = concertService;
        this.ticketService = ticketService;

    }

    private void clearFields() {
        textFieldFirstNameSignUp.setText("");
        textFieldFirstNameSignUp.setText("");
        textFieldUsernameSignUp.setText("");
        passwordFieldPasswordSignUp.setText("");
        textFieldUsernameLogIn.setText("");
        passwordFieldPasswordLogIn.setText("");
    }

    public void handleSignUp() {
        try {
            User newUser = new User(textFieldFirstNameSignUp.getText(),
                    textFieldLastNameSignUp.getText(),
                    textFieldUsernameSignUp.getText(),
                    PasswordHashing.hashPassword(passwordFieldPasswordSignUp.getText()));

            userService.registerUser(newUser);
            User savedUser = userService.getUserByUsername(newUser.getUsername());
            clearFields();

            FXMLLoader loader = new FXMLLoader();
            loader.setLocation(getClass().getResource("user-view.fxml"));
            AnchorPane layout = loader.load();
            Stage stage = new Stage();
            stage.setTitle("Social Network");
            stage.initModality(Modality.WINDOW_MODAL);
            stage.setScene(new Scene(layout));
            UserController userController = loader.getController();
            userController.setService(savedUser, userService, friendshipService, friendshipRequestService, messageService);
            stage.show();

        } catch (Exception e) {
            UserAlert.showMessage(null, Alert.AlertType.ERROR, "Error", e.getMessage());
        }
    }

    public void handleLogIn() {
        try {
            User user = userService.checkUser(textFieldUsernameLogIn.getText(), PasswordHashing.hashPassword(passwordFieldPasswordLogIn.getText()));
            clearFields();

            FXMLLoader loader = new FXMLLoader();
            loader.setLocation(getClass().getResource("user-view.fxml"));
            AnchorPane layout = loader.load();
            Stage stage = new Stage();
            stage.setTitle("Social Network");
            stage.initModality(Modality.WINDOW_MODAL);
            stage.setScene(new Scene(layout));
            UserController userController = loader.getController();
            userController.setService(user, userService, friendshipService, friendshipRequestService, messageService);
            stage.show();

        } catch (Exception e) {
            UserAlert.showMessage(null, Alert.AlertType.ERROR, "Error", e.getMessage());
        }
    }

}
