<?php
/* Log out process, unsets and destroys session variables */
session_start();
session_unset();
session_destroy(); 
?>
<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <title>Error</title>
  <?php include 'css/css.html'; ?>
</head>

<body>
    <div class="form">
          <h3>Bạn đã đăng xuất khỏi thiết bị!</h3>
          <br>
          
          <a href="index.php"><button class="button button-block"/>Trở về trang chủ</button></a>

    </div>
</body>
</html>
