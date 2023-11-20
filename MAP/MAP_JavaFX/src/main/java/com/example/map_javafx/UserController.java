package com.example.map_javafx;

import com.example.domain.User;
import com.example.controller.EditUserController;
import com.example.controller.UserAlert;
import com.example.utils.events.UserChangeEvent;
import com.example.service.UserService;
import com.example.utils.observer.Observer;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Modality;
import javafx.stage.Stage;

import java.io.IOException;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class UserController implements Observer<UserChangeEvent> {

    UserService userService;

    ObservableList<User> userObservableList = FXCollections.observableArrayList();

    @FXML
    TableView<User> tableView;
    @FXML
    TableColumn<User, Long> tableColumnId;
    @FXML
    TableColumn<User,String> tableColumnFirstName;
    @FXML
    TableColumn<User,String> tableColumnLastName;
    @FXML
    TableColumn<User,String> tableColumnUserName;

    public void setService(UserService userService) {
        this.userService = userService;
        this.userService.addObserver(this);
        initObservableList();
    }

    @FXML
    public void initialize() {
        tableColumnId.setCellValueFactory(new PropertyValueFactory<User, Long>("id"));
        tableColumnFirstName.setCellValueFactory(new PropertyValueFactory<User, String>("firstName"));
        tableColumnLastName.setCellValueFactory(new PropertyValueFactory<User, String>("lastName"));
        tableColumnUserName.setCellValueFactory(new PropertyValueFactory<User, String>("username"));
        tableView.setItems(userObservableList);
    }

    private void initObservableList() {
        Iterable<User> users = userService.getAllUsers();
        List<User> userList = StreamSupport.stream(users.spliterator(), false)
                .collect(Collectors.toList());
        userObservableList.setAll(userList);
    }


    public void handleDeleteUser(ActionEvent actionEvent) {
        User selected = (User) tableView.getSelectionModel().getSelectedItem();
        if (selected != null) {
            try {
                userService.removeUser(selected.getId());
                UserAlert.showMessage(null, Alert.AlertType.INFORMATION, "Delete", "Userul a fost sters cu succes!");
            } catch (Exception e) {
                UserAlert.showErrorMessage(null, e.getMessage());
            }
        }
        else
            UserAlert.showErrorMessage(null, "Nu ati selectat nici un User!");
    }

    @Override
    public void update(UserChangeEvent userChangeEvent) {
        initObservableList();
    }

    @FXML
    public void handleUpdateUser(ActionEvent ev) {
        User selected = tableView.getSelectionModel().getSelectedItem();
        if (selected != null) {
            showUserEditDialog(selected);
        } else
            UserAlert.showErrorMessage(null, "Nu ati selectat nici un User!");
    }

    @FXML
    public void handleAddUser(ActionEvent ev) {
        showUserEditDialog(null);
    }

    public void showUserEditDialog(User user) {
        try {
            // create a new stage for the popup dialog.
            FXMLLoader editUserLoader = new FXMLLoader();
            editUserLoader.setLocation(getClass().getResource("edit-user-view.fxml"));
            AnchorPane editUserLayout = editUserLoader.load();

            // Create the dialog Stage.
            Stage dialogStage = new Stage();
            dialogStage.setTitle("Edit User");
            dialogStage.initModality(Modality.WINDOW_MODAL);
            //dialogStage.initOwner(primaryStage);
            Scene scene = new Scene(editUserLayout);
            dialogStage.setScene(scene);

            EditUserController editUserController = editUserLoader.getController();
            editUserController.setService(userService, dialogStage, user);

            dialogStage.show();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

}