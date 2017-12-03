<?php
/* The password reset form, the link to this page is included
   from the forgot.php email message
*/
require 'db.php';
session_start();

// Make sure email and hash variables aren't empty
if( isset($_GET['mssv']) && !empty($_GET['mssv']) AND isset($_GET['hash']) && !empty($_GET['hash']) )
{
    $mssv = $mysqli->escape_string($_GET['mssv']); 
    $hash = $mysqli->escape_string($_GET['hash']); 

    // Make sure user email with matching hash exist
    $result = $mysqli->query("SELECT * FROM users WHERE mssv='$mssv' AND hash='$hash'");

    if ( $result->num_rows == 0 )
    { 
        $_SESSION['message'] = "URL đặt lại mật khẩu không hợp lệ!";
        header("location: error.php");
    }
}
else {
    $_SESSION['message'] = "Xác nhận thất bại, vui lòng thử lại!";
    header("location: error.php");  
}
?>
<!DOCTYPE html>
<html >
<head>
  <meta charset="UTF-8">
  <title>Reset Your Password</title>
  <?php include 'css/css.html'; ?>
</head>

<body>
    <div class="form">

          <h1>Choose Your New Password</h1>
          
          <form action="reset_password.php" method="post">
              
          <div class="field-wrap">
            <label>
              New Password<span class="req">*</span>
            </label>
            <input type="password"required name="newpassword" autocomplete="off"/>
          </div>
              
          <div class="field-wrap">
            <label>
              Confirm New Password<span class="req">*</span>
            </label>
            <input type="password"required name="confirmpassword" autocomplete="off"/>
          </div>
          
          <!-- This input field is needed, to get the email of the user -->
          <input type="hidden" name="mssv" value="<?= $mssv ?>">    
          <input type="hidden" name="hash" value="<?= $hash ?>">    
              
          <button class="button button-block"/>Apply</button>
          
          </form>

    </div>
<script src='http://cdnjs.cloudflare.com/ajax/libs/jquery/2.1.3/jquery.min.js'></script>
<script src="js/index.js"></script>

</body>
</html>
