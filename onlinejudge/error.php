<?php
/* Displays all error messages */
session_start();
?>
<!DOCTYPE html>
<html>
<head>
<link href="img/logo.png" rel="icon"> 
  <title>Lỗi</title>
  <?php include 'css/css.html'; ?>
  <meta charshet="utf-8" />	
</head>
<body>
<div class="bg"> </div>
<div class="form">
    <h1>LỖI</h1>
    <p>
    <?php 
    if( isset($_SESSION['message']) AND !empty($_SESSION['message']) ): 
        echo '<h3>' . $_SESSION['message'] . '</h3>';    
    else:
        header( "location: index.php" );
    endif;
    ?>
    </p>     
    <a href="index.php"><button class="button button-block"/>Trở về trang chủ</button></a>
</div>
</body>
</html>
