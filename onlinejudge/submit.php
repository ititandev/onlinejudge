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
      <meta charshet="utf-8" />	
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
                     <a class="nav-link" href="submit.php"><strong>Nộp bài</strong>
                     <span class="sr-only">(current)</span>
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
                        <?php
                            echo $_SESSION['mssv'];
                        ?>
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
         <h3 class="mt-5">Nộp bài</h3>
         <p>Nộp file zip nén bài tập lớn tại đây.</p>

         <form action="" method="post" enctype="multipart/form-data">
         <div class="form-group">
          <select class="form-control" id="selectass" onchange="document.getElementById('text_content').value=this.options[this.selectedIndex].text">
            <option value="" disabled selected>Chọn bài tập lớn</option>
            <?php
                $conf = parse_ini_file($config_path . "/onlinejudge.conf");
                for($i = 0; $i < $conf["ass_num"]; $i++)
                    if (isset($conf["ass". $i . "_name"]))
                    {
                        $result = $mysqli->query("SELECT * FROM ass_map WHERE mssv='$mssv' AND ass_name='" . $conf["ass". $i . "_name"] . "'");
                        if ($result->num_rows > 0)
                            echo '<option>' . $conf["ass" . $i . "_name"] . '</option>';
                    }
            ?>
          </select>
          <input type="hidden" name="ass_name" id="text_content" value="" />
          </div>
         <div class="form-group">
            <input type="file" name="fileUpload" class="file" style="visibility: hidden;position: absolute;">
            <div class="input-group col-xs-12">
               <input type="text" class="form-control input-lg" disabled placeholder="Chọn .zip chứa bài tập lớn">
               <span class="input-group-btn">
               <button class="browse btn btn-primary input-lg" type="button"><i class="glyphicon glyphicon-search"></i> Chọn</button>
               </span>
            </div>
         </div>
         <div class="text-center">
         <input type="submit" name="up" class="btn btn-primary center-block" value="Nộp bài" style="width: 150px">
         </div>

         <?php
          echo '<br>';
          $conf = parse_ini_file($config_path . "/onlinejudge.conf");
          if(isset($_POST['up']) && isset($_FILES['fileUpload']))
          {
            if ($_POST['ass_name'] == "")
            {
                echo '<div style="color: #ca5354;">Chọn một bài tập lớn để nộp</div> ';
            }
            else
            {
              $MSSV = $_SESSION['mssv'];
              if($_FILES['fileUpload']['error']>0)
              echo '<div style="color: #ca5354;">Upload thất bại</div> ';
              else if (preg_match("/.+\.zip/", $_FILES['fileUpload']['name']) != 1)     
                  echo '<div style="color: #ca5354;">Vui lòng nộp file .zip</div> ';
              else
              {
                  $i = 1;
                  for ($i = 1;; $i++) 
                  {
                      $file = $conf["upload_path"] . "/" . $_POST["ass_name"] . '/' . $MSSV . '_' . $i . '.zip';
                      if (file_exists($file) == 0)
                      {
                          move_uploaded_file($_FILES['fileUpload']['tmp_name'],$file);
                          chmod($file, 0777);
                          break;
                      }
                  }
                  echo '<div style="color: #00cc00" >' ;
                  echo 'Nộp bài thành công lần vào ' . $_POST["ass_name"] . ' <br>';
                  echo 'Dung lượng: ' . round((int)$_FILES['fileUpload']['size']/1024, 2) .'KB';
                  echo '</div>';
                  
              }
            }
                  
          }
          ?>
         </form>
         





         <!--<h1 class="mt-5">Kết quả</h1>
         <div class="form-group">
            <label for="exampleFormControlTextarea1">Thông tin chấm điểm</label>
            <textarea class="form-control" id="exampleFormControlTextarea1" rows="3" style=" height: 150px;display: block; margin: 0 auto;">
            </textarea>
         </div>
         -->
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