package org.example.demo;

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
import org.example.domain.User;
import org.example.service.ConcertService;
import org.example.service.TicketService;
import org.example.service.UserService;

public class LogInSignUpController {
    @FXML
    private TextField textFieldEmailLogIn;
    @FXML
    private PasswordField passwordFieldPasswordLogIn;
    @FXML
    private Button buttonLogIn;
    @FXML
    private TextField textFieldNameSignUp;
    @FXML
    private TextField textFieldEmailSignUp;
    @FXML
    private TextField passwordFieldPasswordSignUp;
    @FXML
    private Button buttonSignUp;

    private UserService userService;

    private TicketService ticketService;

    private ConcertService concertService;

    public void setService(UserService userService, TicketService ticketService, ConcertService concertService) {
        this.userService = userService;
        this.ticketService = ticketService;
        this.concertService = concertService;
    }

    private void clearFields() {
        textFieldNameSignUp.setText("");
        textFieldEmailSignUp.setText("");
        passwordFieldPasswordSignUp.setText("");
        textFieldEmailLogIn.setText("");
        passwordFieldPasswordLogIn.setText("");
    }

    public void handleSignUp() {
        try {
            User newUser = new User(textFieldNameSignUp.getText(),
                    textFieldEmailSignUp.getText(),
                    passwordFieldPasswordSignUp.getText());

            User savedUser = userService.registerUser(newUser);
            clearFields();

            FXMLLoader loader = new FXMLLoader();
            loader.setLocation(getClass().getResource("ticket-view.fxml"));
            AnchorPane layout = loader.load();
            Stage stage = new Stage();
            stage.setTitle("Festival Ticket Store");
            stage.initModality(Modality.WINDOW_MODAL);
            stage.setScene(new Scene(layout));
            TicketController ticketController = loader.getController();
            ticketController.setService(savedUser, userService, ticketService, concertService);
            stage.show();

        } catch (Exception e) {
            UserAlert.showMessage(null, Alert.AlertType.ERROR, "Error", e.getMessage());
        }
    }

    public void handleLogIn() {
        try {
            User user = userService.logInUser(textFieldEmailLogIn.getText(), passwordFieldPasswordLogIn.getText());
            clearFields();

            FXMLLoader loader = new FXMLLoader();
            loader.setLocation(getClass().getResource("ticket-view.fxml"));
            AnchorPane layout = loader.load();
            Stage stage = new Stage();
            stage.setTitle("Festival Ticket Store");
            stage.initModality(Modality.WINDOW_MODAL);
            stage.setScene(new Scene(layout));
            TicketController ticketController = loader.getController();
            ticketController.setService(user, userService, ticketService, concertService);
            stage.show();

        } catch (Exception e) {
            UserAlert.showMessage(null, Alert.AlertType.ERROR, "Error", e.getMessage());
        }
    }

}
