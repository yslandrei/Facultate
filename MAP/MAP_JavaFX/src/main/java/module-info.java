module com.example.map_javafx {
    requires javafx.controls;
    requires javafx.fxml;
    requires org.controlsfx.controls;
    requires com.dlsc.formsfx;
    requires java.sql;

    exports com.example.view;
    opens com.example.view to javafx.fxml;

    exports com.example.domain;
    opens com.example.domain to javafx.base;

    exports com.example.controller;
    opens com.example.controller to javafx.fxml;

    exports com.example.map_javafx;
    opens com.example.map_javafx to javafx.fxml;
    exports com.example.utils.events;
    opens com.example.utils.events to javafx.fxml;


}