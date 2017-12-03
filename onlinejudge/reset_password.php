<?php
/* Password reset process, updates database with new user password */
require 'db.php';
session_start();

// Make sure the form is being submitted with method="post"
if ($_SERVER['REQUEST_METHOD'] == 'POST') { 

    // Make sure the two passwords match
    if ( $_POST['newpassword'] == $_POST['confirmpassword'] ) { 

        $new_password = password_hash($_POST['newpassword'], PASSWORD_BCRYPT);
        
        // We get $_POST['email'] and $_POST['hash'] from the hidden input field of reset.php form
        $mssv = $mysqli->escape_string($_POST['mssv']);
        $hash = $mysqli->escape_string($_POST['hash']);
        
        $sql = "UPDATE users SET password='$new_password', hash='$hash' WHERE mssv='$mssv'";

        if ( $mysqli->query($sql) ) {

        $_SESSION['message'] = "Mật khẩu đã được đặt lại thành công!";
        header("location: success.php");    

        }

    }
    else {
        $_SESSION['message'] = "Mật khẩu không khớp!";
        header("location: error.php");    
    }

}
?>