<?php
/* User login process, checks if user exists and password is correct */

// Escape mssv to protect against SQL injections
$mssv = $mysqli->escape_string($_POST['mssv']);
$result = $mysqli->query("SELECT * FROM users WHERE mssv='$mssv'");

if ( $result->num_rows == 0 ){ // User doesn't exist
    $_SESSION['message'] = "Tài khoản với MSSV (". $_POST['mssv'] .") này không tồn tại!";
    header("location: error.php");
}
else { // User exists
    $user = $result->fetch_assoc();

    if ( password_verify($_POST['password'], $user['password']) ) {
        
        $_SESSION['mssv'] = $user['mssv'];
        $_SESSION['first_name'] = $user['first_name'];
        $_SESSION['last_name'] = $user['last_name'];
        $_SESSION['active'] = $user['active'];
        
        // This is how we'll know the user is logged in
        $_SESSION['logged_in'] = true;
        if ($mssv == 'admin')
        {
            $_SESSION['message'] = "";
            $_SESSION['as_admin'] = true;
            header("location: admin.php");
        }
        else
        {
            $_SESSION['message'] = "";
            header("location: submit.php");
        }
    }
    else {
        $_SESSION['message'] = "Bạn nhập sai mật khẩu! Vui lòng thử lại!";
        header("location: error.php");
    }
}

