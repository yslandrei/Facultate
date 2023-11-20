package com.example.controller;

import com.example.domain.User;
import com.example.service.UserService;
import javafx.fxml.FXML;
import javafx.scene.control.Alert;
import javafx.scene.control.TextField;
import javafx.stage.Stage;

public class EditUserController {
    @FXML
    private TextField textFieldId;
    @FXML
    private TextField textFieldFirstName;
    @FXML
    private TextField textFieldLastName;
    @FXML
    private TextField textFieldUsername;
    @FXML
    private TextField textFieldPassword;

    private UserService userService;

    Stage dialogStage;

    User user;

    @FXML
    private void initialize() {
    }

    public void setService(UserService userService,  Stage stage, User user) {
        this.userService = userService;
        this.dialogStage = stage;
        this.user = user;
        if (null != user) {
            setFields(user);
            textFieldId.setEditable(false);
        }
    }

    @FXML
    public void handleSave() {
        String id = textFieldId.getText();
        String firstName = textFieldFirstName.getText();
        String lastName = textFieldLastName.getText();
        String username = textFieldUsername.getText();
        String password = textFieldPassword.getText();
        User u = new User(Long.parseLong(id), firstName, lastName, username, password);
        if (null == this.user)
            saveUser(u);
        else
            updateUser(u);
    }

    private void updateUser(User u) {
        try {
            this.userService.updateUser(u);
            UserAlert.showMessage(null, Alert.AlertType.INFORMATION,"Modificare User","Userul a fost modificat");
        } catch (Exception e) {
            UserAlert.showErrorMessage(null, e.getMessage());
        }
        dialogStage.close();
    }


    private void saveUser(User u) {
        try {
            this.userService.addUser(u);
            dialogStage.close();
            UserAlert.showMessage(null, Alert.AlertType.INFORMATION,"Salvare User","Userul a fost salvat");
        } catch (Exception e) {
            UserAlert.showErrorMessage(null, e.getMessage());
        }
        dialogStage.close();
    }

    private void clearFields() {
        textFieldId.setText("");
        textFieldFirstName.setText("");
        textFieldLastName.setText("");
        textFieldUsername.setText("");
        textFieldPassword.setText("");
    }

    private void setFields(User u) {
        textFieldId.setText(u.getId().toString());
        textFieldFirstName.setText(u.getFirstName());
        textFieldLastName.setText(u.getLastName());
        textFieldUsername.setText(u.getUsername());
        textFieldPassword.setText(u.getPassword());
    }

    @FXML
    public void handleCancel(){
        dialogStage.close();
    }

}
