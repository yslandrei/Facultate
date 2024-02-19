package com.example.map_javafx;

import com.example.domain.FriendshipRequestStatus;
import com.example.domain.User;
import com.example.service.FriendshipRequestService;
import com.example.service.FriendshipService;
import com.example.service.MessageService;
import com.example.service.UserService;
import com.example.utils.password.PasswordHashing;
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

    private FriendshipService friendshipService;

    private FriendshipRequestService friendshipRequestService;

    private MessageService messageService;

    public void setService(UserService userService, FriendshipService friendshipService, FriendshipRequestService friendshipRequestService, MessageService messageService) {
        this.userService = userService;
        this.friendshipService = friendshipService;
        this.friendshipRequestService = friendshipRequestService;
        this.messageService = messageService;
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
