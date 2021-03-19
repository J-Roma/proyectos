<?php
          
$servername = "sql107.byethost7.com";
$username = "b7_20027752";
$password = "Jhosaid18";
$dbname = "b7_20027752_webview";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 
/*
$sql = "insert into usuarios (correo, Nombre, Apellido, tag) 
            values ('javimencast@hotmail.com','Javier','Mendoza','0D C0 4E 38')";



if ($conn->query($sql) === TRUE) {
    echo "Se registro con exito";
} else {
    echo "Error: " . $sql . "<br>" . $conn->error;
}    
$conn->close(); 
 */
  
?>