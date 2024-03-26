package org.example.demo;

import javafx.application.Application;
import javafx.beans.binding.Bindings;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.stage.Stage;
import org.example.domain.Concert;
import org.example.domain.User;
import org.example.service.ConcertService;
import org.example.service.TicketService;
import org.example.service.UserService;
import org.example.utils.observer.Observer;

import java.time.LocalDateTime;

public class TicketController implements Observer {
    @FXML
    public DatePicker datePicker;
    @FXML
    public TableView<Concert> tableViewConcerts;
    @FXML
    public TableColumn<Concert, String> artistColumn;
    @FXML
    public TableColumn<Concert, String> dateColumn;
    @FXML
    public TableColumn<Concert, String> locationColumn;
    @FXML
    public TableColumn<Concert, Integer> availableTicketsColumn;
    @FXML
    public TextField textFieldBuyer;
    @FXML
    public TextField textFieldSeats;
    @FXML
    public Button buttonBuyTicket;

    private ObservableList<Concert> concertObservableList = FXCollections.observableArrayList();

    private User loggedUser;

    private UserService userService;
    private TicketService ticketService;
    private ConcertService concertService;

    public void setService(User savedUser, UserService userService, TicketService ticketService, ConcertService concertService) {
        this.loggedUser = savedUser;
        this.userService = userService;
        this.ticketService = ticketService;
        this.concertService = concertService;
        this.ticketService.addObserver(this);

        tableViewConcerts.setItems(concertObservableList);
        concertObservableList.setAll(concertService.getAllConcerts());
    }

    @FXML
    public void initialize() {
        artistColumn.setCellValueFactory(cellData ->
                Bindings.createStringBinding(() -> cellData.getValue().getArtist()));

        dateColumn.setCellValueFactory(cellData ->
                Bindings.createObjectBinding(() -> cellData.getValue().getDate().toString()));

        locationColumn.setCellValueFactory(cellData ->
                Bindings.createStringBinding(() -> cellData.getValue().getLocation()));

        availableTicketsColumn.setCellValueFactory(cellData ->
                Bindings.createObjectBinding(() -> cellData.getValue().getAvailableTickets()));

        tableViewConcerts.setRowFactory(tv -> new TableRow<Concert>() {
            @Override
            protected void updateItem(Concert item, boolean empty) {
                super.updateItem(item, empty);
                if (item == null || empty) {
                    setStyle("");
                } else if (item.getAvailableTickets() == 0) {
                    setStyle("-fx-background-color: tomato;");
                } else {
                    setStyle("");
                }
            }
        });


        datePicker.valueProperty().addListener((observable, oldValue, newValue) -> {
            concertObservableList.setAll(concertService.getConcertsFromDay(datePicker.getValue().atStartOfDay()));
        });

    }

    public void handleBuyTicket(ActionEvent actionEvent) {
        Concert selectedConcert = tableViewConcerts.getSelectionModel().getSelectedItem();
        if (selectedConcert == null) {
            UserAlert.showMessage(null, Alert.AlertType.ERROR, "Error", "Please select a concert!");
            return;
        }
        if (textFieldBuyer.getText().isEmpty()) {
            UserAlert.showMessage(null, Alert.AlertType.ERROR, "Error", "Please enter the buyer's name!");
            return;
        }
        if (textFieldSeats.getText().isEmpty()) {
            UserAlert.showMessage(null, Alert.AlertType.ERROR, "Error", "Please enter the number of seats!");
            return;
        }
        try {
            Integer.parseInt(textFieldSeats.getText());
        } catch (Exception e) {
            UserAlert.showMessage(null, Alert.AlertType.ERROR, "Error", "Please enter a valid number of seats!");
            return;
        }

        try {
            ticketService.buyTicket(selectedConcert, loggedUser, textFieldBuyer.getText(), Integer.parseInt(textFieldSeats.getText()));
        } catch (Exception e) {
            UserAlert.showMessage(null, Alert.AlertType.ERROR, "Error", e.getMessage());
        }
    }

    @Override
    public void update() {
        concertObservableList.setAll(concertService.getConcertsFromDay(datePicker.getValue().atStartOfDay()));
    }
}
