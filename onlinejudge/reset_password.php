<?php
/* Password reset process, updates database with new user password */
require 'db.php';
session_start();

// Make sure the form is being submitted with method="post"
if ($_SERVER['REQUEST_METHOD'] == 'POST') 
{
    $mssv = $_POST['mssv'];
    $hash = $_POST['hash'];
    $result = $mysqli->query("SELECT * FROM users WHERE mssv='$mssv' AND hash='$hash'");
    if ( $result->num_rows == 0 )
    { 
        $_SESSION['message'] = "URL đặt lại mật khẩu không hợp lệ!";
        header("location: error.php");
    }
    else
    {
        $result = $mysqli->query("SELECT * FROM users WHERE mssv='" . $_POST['mssv'] . "'");
        $user = $result->fetch_assoc();
        
        if (password_verify($_POST['oldpassword'],$user['password']))
        {
            // Make sure the two passwords match
            if ( $_POST['newpassword'] == $_POST['confirmpassword'] ) { 

                $new_password = password_hash($_POST['newpassword'], PASSWORD_BCRYPT);
                
                // We get $_POST['email'] and $_POST['hash'] from the hidden input field of reset.php form
                $mssv = $mysqli->escape_string($_POST['mssv']);
                $hash = $mysqli->escape_string($_POST['hash']);
                
                $sql = "UPDATE users SET password='$new_password', hash='$hash' WHERE mssv='$mssv'";

                if ( $mysqli->query($sql) ) 
                {
                    $mysqli->query("UPDATE users SET hash = MD5(RAND()) WHERE mssv='$mssv'");
                    $_SESSION['message'] = "Mật khẩu đã được đặt lại thành công!";
                    header("location: success.php");    
                }
            }
            else {
                $_SESSION['message'] = "Mật khẩu không khớp!";
                header("location: error.php");    
            }
        }
        else
        {
            $_SESSION['message'] = "Mật khẩu cũ không đúng!";
            header("location: error.php");  
        }
    }
}
?>