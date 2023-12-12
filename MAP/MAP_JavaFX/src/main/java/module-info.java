module com.example.map_javafx {
    requires javafx.controls;
    requires javafx.fxml;
    requires org.controlsfx.controls;
    requires com.dlsc.formsfx;
    requires java.sql;

    exports com.example.domain;
    opens com.example.domain to javafx.base;

    exports com.example.map_javafx;
    opens com.example.map_javafx to javafx.fxml;

}