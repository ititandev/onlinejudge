<?php 
/* Reset your password form, sends reset.php password link */
require 'db.php';
session_start();

// Check if form submitted with method="post"
if ( $_SERVER['REQUEST_METHOD'] == 'POST' ) 
{   
    $mssv = $mysqli->escape_string($_POST['mssv']);
    $result = $mysqli->query("SELECT * FROM users WHERE mssv='$mssv'");

    if ( $result->num_rows == 0 ) // User doesn't exist
    { 
        $_SESSION['message'] = "Tài khoản với MSSV này không tồn tại!";
        header("location: error.php");
    }
    else { // User exists (num_rows != 0)

        $user = $result->fetch_assoc(); // $user becomes array with user data
        
        $email = $user['mssv'] . '@hcmut.edu.vn';
        $hash = $user['hash'];
        $first_name = $user['first_name'];

        // Session message to display on success.php
        $_SESSION['message'] = "<p>Vui lòng kiểm tra email <span>$email</span>"
        . " và truy cập link được gửi để hoàn thành đặt lại mật khẩu!</p>";

        // Send registration confirmation link (reset.php)
        $to      = $email;
        $subject = 'Đặt lại mật khẩu';
        $message_body = '
        Hello '.$first_name.',

        Bạn đã yêu cầu đặt lại mật khẩu!

        Xin hãy truy cập link này và hoàn thành đặt lại mật khẩu:

        http://vre.hcmut.edu.vn/onlinejudge/reset.php?mssv='.$mssv.'&hash='.$hash;  

        mail($to, $subject, $message_body);

        header("location: success.php");
  }
}
?>
<!DOCTYPE html>
<html>
<head>
<link href="img/logo.png" rel="icon"> 
  <title>Đặt lại mật khẩu</title>
  <?php include 'css/css.html'; ?>
  <meta charshet="utf-8" />	
</head>

<body>
<div class="bg"> </div>
  <div class="form">

    <h1>Đặt lại mật khẩu</h1>

    <form action="forgot.php" method="post">
     <div class="field-wrap">
      <label>
        MSSV<span class="req">*</span>
      </label>
      <input type="text" required autocomplete="off" name="mssv"/>
    </div>
    <button class="button button-block"/>Đặt lại</button>
    </form>
  </div>
          
<script src='http://cdnjs.cloudflare.com/ajax/libs/jquery/2.1.3/jquery.min.js'></script>
<script src="js/index.js"></script>
</body>

</html>
