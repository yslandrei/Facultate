package org.example.demo;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;
import org.example.service.*;

import java.io.IOException;

public class FestivalApplication extends Application {

    private UserService userService;

    private TicketService ticketService;

    private ConcertService concertService;

    public FestivalApplication(UserService userService, ConcertService concertService, TicketService ticketService) {
        this.userService = userService;
        this.ticketService = ticketService;
        this.concertService = concertService;
    }

    @Override
    public void start(Stage stage) throws IOException {
        initView(stage);
        stage.show();
    }

    private void initView(Stage primaryStage) throws IOException {

        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource("org.example/log-in-sign-up-view.fxml"));
        AnchorPane layout = loader.load();
        primaryStage.setScene(new Scene(layout));

        LogInSignUpController logInSignUpController = loader.getController();
        logInSignUpController.setService(userService, ticketService, concertService);
    }

    public static void main(String[] args) {
        launch();
    }
}