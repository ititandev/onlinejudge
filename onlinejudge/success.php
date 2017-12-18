<?php
/* Displays all successful messages */
session_start();
?>
<!DOCTYPE html>
<html>
<head>
  <title>Success</title>
  <?php include 'css/css.html'; ?>
  <link href="img/logo.png" rel="icon"> 
</head>
<body>
<div class="bg"> </div>
<div class="form">
    <h1><?= 'Thành công'; ?></h1>
    <p>
    <?php 
    if( isset($_SESSION['message']) AND !empty($_SESSION['message']) ):
        echo $_SESSION['message'];    
    else:
        header( "location: index.php" );
    endif;
    ?>
    </p>
    <a href="index.php"><button class="button button-block"/>Về lại trang chủ</button></a>
</div>
</body>
</html>
