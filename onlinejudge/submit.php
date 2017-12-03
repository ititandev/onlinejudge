<?php
/* Displays user information and some useful messages */
session_start();

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
      <meta charset="utf-8">
      <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
      <meta name="description" content="">
      <meta name="author" content="">
      <title>Nộp bài-Kết quả</title>
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
                  <li class="nav-item active">
                     <a class="nav-link" href="#">Nộp bài và kết quả
                     <span class="sr-only">(current)</span>
                     </a>
                  </li>
                  <li class="nav-item">
                     <a class="nav-link" href="#">Lịch sử nộp bài</a>
                  </li>
                  <li class="nav-item">
                     <a class="nav-link" href="#">   &emsp;   &emsp; </a>
                  </li>
                  <li class="nav-item">
                     <a class="nav-link" href="#">MSSV</a>
                  </li>
                  <li class="nav-item">
                     <a class="nav-link" href="logout.php">Đăng xuất</a>
                  </li>
               </ul>
            </div>
         </div>
      </nav>
      <!-- Page Content -->
      <div class="container">
         <h1 class="mt-5">Nộp bài</h1>
         <p>Nộp file zip nén bài tập lớn tại đây.</p>

         <form action="" method="post" enctype="multipart/form-data">
         <div class="form-group">
          <label for="sel1">Chọn bài tập lớn:</label>
          <select class="form-control" id="selectass">
            <option>ass1</option>
            <option>ass2</option>
          </select>
          </div>
         <div class="form-group">
            <input type="file" name="fileUpload" class="file" style="visibility: hidden;position: absolute;">
            <div class="input-group col-xs-12">
               <span class="input-group-addon"><i class="glyphicon glyphicon-picture"></i></span>
               <input type="text" class="form-control input-lg" disabled placeholder="Upload Image">
               <span class="input-group-btn">
               <button class="browse btn btn-primary input-lg" type="button"><i class="glyphicon glyphicon-search"></i> Browse</button>
               </span>
            </div>
         </div>
         <div class="text-center">
         <input type="submit" name="up" class="btn btn-primary center-block" value="Nộp bài" style="width: 150px">
         </div>
         </form>
         <?php
          echo isset($_POST['up']) . ' <br>' . isset($_FILES['fileUpload']);
          if(isset($_POST['up']) && isset($_FILES['fileUpload']))
          {
              if($_FILES['fileUpload']['error']>0)
              echo '<div class="row" style=" font-size: 120%;"> <label for="name" style="color: #ca5354; width: 500px;" >Upload thất bại</label></div> ';
              else if ($_FILES['fileUpload']['type'] != 'application/zip')
                  echo "Vui lòng nộp file .zip";
              else
              {
                  for ($i = 0;; $i++) 
                  {
                      $file = './Upload/' . $MSSV . '_' . $i . '.zip';
                      //echo 'check file ' . $file . ': '. file_exists($file) . '<br>';
                      if (file_exists($file) == 0)
                      {
                          move_uploaded_file($_FILES['fileUpload']['tmp_name'],$file);
                          chmod($file, 0777);
                          break;
                      }
                  }
                  echo '<div class="row" style=" font-size: 120%;"> <label for="name" style="color: #00cc00; width: 500px;" >' ;
                  echo 'Sinh viên ' . $MSSV . ' nộp bài thành công <br>';
                  echo 'Dung lượng: ' . ((int)$_FILES['fileUpload']['size']/1024) .'KB';
                  echo '</label></div>';
                  
              }
                  
          }
          ?>





         <h1 class="mt-5">Kết quả</h1>
         <div class="form-group">
            <label for="exampleFormControlTextarea1">Thông tin chấm điểm</label>
            <textarea class="form-control" id="exampleFormControlTextarea1" rows="3" style=" height: 150px;display: block; margin: 0 auto;">
            </textarea>
         </div>
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