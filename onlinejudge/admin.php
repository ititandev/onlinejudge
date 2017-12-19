<?php
/* Displays user information and some useful messages */
session_start();
require 'db.php';
// Check if user is logged in using the session variable
if ( $_SESSION['logged_in'] != 1  || $_SESSION['as_admin'] != 1) {
    $_SESSION['message'] = "Bạn phải đăng nhập admin trước khi sử dụng!";
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
      <title>Kết quả sinh viên</title>
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
                     <a class="nav-link" href="admin.php"><strong>Kết quả sinh viên</strong></a>
                     <span class="sr-only">(current)</span>
                  </li>
                  <li class="nav-item">
                     <a class="nav-link" href="export.php">Xuất điểm</a>
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
         <h3 class="mt-5">Xuất điểm</h3>
         <p>Chọn assignment và xem bảng kết quả.</p>

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
         <input type="submit" name="view" class="btn btn-primary center-block" value="Xem kết quả" style="width: 150px">
         </div>
         
        <?php
            if(isset($_POST['view']))
            {
                echo '<br>';
                if ($_POST['ass_name'] == "")
                {
                    echo '<div style="color: #ca5354;">Chọn một bài tập lớn để xem</div> <br>';
                }
                else
                {
                    echo '<div class="table-responsive">          
                    <table class="table table-bordered table-hover">';
                    echo '<thead><tr><th>Sinh viên</th><th>Điểm</th>';
                    echo '<th>Lần nộp</th><th>Thời gian</th><tbody>';
                    $ass_name = $_POST['ass_name'];
                    $conf = parse_ini_file($config_path . "/onlinejudge.conf");
                    $source_path = $conf['source_path'];
                    $result = $mysqli->query("SELECT * FROM ass_map WHERE ass_name='$ass_name'");
                    while ($user = $result->fetch_assoc())
                    {
                        $score = 0; $date = '';
                        $times = 1;
                        $mssv = $user['mssv'];
                        for (;; $times++)
                        {
                            $dir = $source_path . '/' . $ass_name . '/' . $mssv . '/' . $times . '/';
                            if (file_exists($dir) == 0)
                            {
                                break;
                            }
                        }
                        $times--;
                        if($times == 0)
                            $score = 13;
                        else
                        {
                            $file = $source_path . '/' . $ass_name . '/' . $mssv . '/' . $times . '/' . 'score.log';
                            if (file_exists($file) == 0)
                                $score = 'waiting';
                            else
                            {
                                $myfile = fopen($file, "r");
                                $date = fgets($myfile);
                                fgets($myfile);
                                $score = fgets($myfile);
                            }
                        }
                        echo "<tr><td>$mssv</td>";
                        echo "<td>$score</td>";
                        echo "<td>$times</td>";
                        echo "<td>$date</td></tr>";
                    }
                    echo '</tbody></table></div>';
                }
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