<?php
    // iot.php
    // Importamos la configuraci�n
    require("conexion.php");
    // Leemos los valores que nos llegan por GET
    $valor = mysqli_real_escape_string($conn, $_GET['valor']);
    // Esta es la instrucci�n para insertar los valores
    $query = "INSERT INTO usuarios(tag) VALUES('".$valor."')";
    $query2 = "INSERT INTO usuarios(tag) VALUES('123asdg')";
    // Ejecutamos la instrucci�n
    mysqli_query($conn, $query);
    mysqli_query($conn, $query2);
    mysqli_close($conn);
 
?>