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
                  <li class="nav-item active">
                     <a class="nav-link" href="result.php"><strong>Kết quả</strong></a>
                     <span class="sr-only">(current)</span>
                  </li>
                  <li class="nav-item">
                     <a class="nav-link" href="history.php">Lịch sử nộp bài</a>
                  </li>
                  <li class="nav-item">
                     <a class="nav-link" href="#">   &emsp;   &emsp; </a>
                  </li>
                  <li class="nav-item">
                     <a class="nav-link" href="submit.php" style="color:#ccffff;">
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
         <h3 class="mt-5">Kết quả</h3>
         <p>Chọn assignment và xem kết quả về lần nộp bài mới nhất.</p>

         <form action="" method="post">
         <div class="form-group">
          <label for="sel1">Chọn bài tập lớn:</label>
            <select class="form-control" id="selectass" onchange="document.getElementById('text_content').value=this.options[this.selectedIndex].text">
            <option value="" disabled selected>Chọn bài tập lớn</option>
            <?php
                $conf = parse_ini_file("onlinejudge.conf");
                for($i = 0; $i < $conf["ass_num"]; $i++)
                    if (isset($conf["ass". $i . "_name"]))
                        echo '<option>' . $conf["ass" . $i . "_name"] . '</option>';
            ?>
            </select>
          </select>
          <input type="hidden" name="ass_name" id="text_content" value="" />
          <script>
              document.getElementById('text_content').value="ass1";
          </script>
          </div>
         <div class="text-center">
         <input type="submit" name="view" class="btn btn-primary center-block" value="Xem kết quả" style="width: 150px">
         </div>
         </form>
         
        




         <div class="form-group">
            <label for="exampleFormControlTextarea1">Thông tin chấm điểm</label>
            <textarea class="form-control" id="exampleFormControlTextarea1" rows="3" style=" height: 150px;display: block; margin: 0 auto;">
            <?php
                if(isset($_POST['view']))
                {
                    $conf = parse_ini_file("onlinejudge.conf");
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
            ?>
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