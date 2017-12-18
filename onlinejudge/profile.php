<?php
/* Displays user information and some useful messages */
session_start();
require 'db.php';
// Check if user is logged in using the session variable
if ( $_SESSION['logged_in'] != 1 ) {
  $_SESSION['message'] = "Bạn phải đăng nhập trước khi sử dụng websise!";
  header("location: error.php");    
}
else {
    // Makes it easier to read
    $first_name = $_SESSION['first_name'];
    $last_name = $_SESSION['last_name'];
    $mssv = $_SESSION['mssv'];
    $active = $_SESSION['active'];
}
?>

<!DOCTYPE html>
<html lang="en">
   <head>
      <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
      <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
      <meta name="description" content="">
      <meta name="author" content="">
      <title>Nộp bài</title>
      <!-- Bootstrap core CSS -->
      <link href="vendor/bootstrap/css/bootstrap.min.css" rel="stylesheet">
      <!-- Custom styles for this template -->
      <link href="css/logo-nav.css" rel="stylesheet">
      <link href="img/logo.png" rel="icon"> 
   </head>
   <body>
      <!-- Navigation -->
      <nav class="navbar navbar-expand-lg navbar-dark bg-dark fixed-top">
         <div class="container">
            <a class="navbar-brand" href="#">
            <img src="img/logo2.png" width="30" height="30" alt="">
            </a>
            <a class="navbar-brand" href="#">
            Chấm điểm tự động
            </a>
            <button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarResponsive" aria-controls="navbarResponsive" aria-expanded="false" aria-label="Toggle navigation">
            <span class="navbar-toggler-icon"></span>
            </button>
            <div class="collapse navbar-collapse" id="navbarResponsive">
               <ul class="navbar-nav ml-auto">
                  <li class="nav-item ">
                     <a class="nav-link" href="submit.php">Nộp bài
                     </a>
                  </li>
                  <li class="nav-item">
                     <a class="nav-link" href="result.php">Kết quả</a>
                  </li>
                  <li class="nav-item">
                     <a class="nav-link" href="history.php">Lịch sử nộp bài</a>
                  </li>
                  <li class="nav-item">
                     <a class="nav-link" href="#">   &emsp;   &emsp; </a>
                  </li>
                  <li class="nav-item">
                     <a class="nav-link" href="profile.php" style="color:#ccffff;">
                     <strong>
                        <?php
                            echo $_SESSION['mssv'];
                        ?>
                        </strong>
                     </a>
                  </li>
                  <li class="nav-item">
                     <a class="nav-link" href="logout.php" style="color:#ffccff;">Đăng xuất</a>
                  </li>
               </ul>
            </div>
         </div>
      </nav>
      <!-- Page Content -->
      <div class="container">
         <h3 class="mt-5">Thông tin cá nhân</h3>
         <p>Xem thông tin cá nhân và thay đổi mật khẩu.</p>

         <form action="" method="post">
         <div class="form-group">
            <select class="form-control" id="selectass" onchange="document.getElementById('text_content').value=this.options[this.selectedIndex].text">
            <option value="" disabled selected>Chọn bài tập lớn</option>
            <?php
                $conf = parse_ini_file($config_path . "/onlinejudge.conf");
                for($i = 0; $i < $conf["ass_num"]; $i++)
                    if (isset($conf["ass". $i . "_name"]))
                        echo '<option>' . $conf["ass" . $i . "_name"] . '</option>';
            ?>
            </select>
          </select>
          <input type="hidden" name="ass_name" id="text_content" value="" />
          </div>
         <div class="text-center">
         <input type="submit" name="reset" class="btn btn-primary center-block" value="Đổi mật khẩu" style="width: 200px">
         </div>
         
         
        <?php
            if(isset($_POST['reset']))
            {
                $mssv = $_SESSION['mssv'];
                $mysqli->query("UPDATE users SET hash = MD5(RAND()) WHERE mssv='$mssv'");
                $result = $mysqli->query("SELECT * FROM users WHERE mssv='$mssv'");
                $user = $result->fetch_assoc(); 
                $hash = $user['hash'];
                header('location: reset.php?mssv=' . $mssv . '&hash=' . $hash);
            }
        ?>
        </form>
         
      </div>
      <!-- /.container -->
      <!-- Bootstrap core JavaScript -->
      <script src="vendor/jquery/jquery.min.js"></script>
      <script src="vendor/bootstrap/js/bootstrap.bundle.min.js"></script>
      <script>
         $(document).on('click', '.browse', function(){
         var file = $(this).parent().parent().parent().find('.file');
         file.trigger('click');
         });
         $(document).on('change', '.file', function(){
         $(this).parent().find('.form-control').val($(this).val().replace(/C:\\fakepath\\/i, ''));
         });
      </script>
   </body>
</html>