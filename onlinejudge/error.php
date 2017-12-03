<?php
/* Displays all error messages */
session_start();
?>
<!DOCTYPE html>
<html>
<head>
  <title>Lỗi</title>
  <?php include 'css/css.html'; ?>
</head>
<body>
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
