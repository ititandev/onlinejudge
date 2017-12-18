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
      <title>Kết quả</title>
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
         <h3 class="mt-5">Kết quả</h3>
         <p>Chọn assignment và xem kết quả về lần nộp bài mới nhất.</p>

         <form action="" method="post">
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
                    $times = 1;
                    $conf = parse_ini_file($config_path . "/onlinejudge.conf");
                    $MSSV = $_SESSION['mssv'];
                    for (;; $times++)
                    {
                        $dir = $conf['source_path'] . '/' . $_POST['ass_name'] . '/' . $MSSV . '/' . $times . '/';
                        if (file_exists($dir) == 0)
                        {
                            break;
                        }
                    }
                    $times--;    
                    if ($times == 0)
                    {
                        echo '<div style="color: #ca5354;" >Sinh viên chưa nộp bài lần nào vào ' . $_POST['ass_name'] . '</div><br>';
                    }
                    else
                    {
                        echo '<h4 style="color: #00cc00;" >Kết quả lần nộp thứ ' . $times . '</h4><br>';
                        $file = $conf["source_path"] . '/' . $_POST["ass_name"] . '/' . $MSSV . '/' . $times . '/' . 'score.log';
                        if (file_exists($file) == 0)
                        {
                            echo '<div style="color: #ca5354" >Bài nộp mới nhất của sinh viên đang được chấm</div><br> ';
                        }  
                        else
                        {
                            $myfile = fopen($file, "r") or die("Unable to open file!");
                            echo '<div class="table-responsive">          
                            <table class="table table-bordered table-hover">';
                            $bool = false;
                            for($i= 1; !feof($myfile); $i++) 
                            {
                                if ($i == 1)
                                    echo '<thead>';
                                if ($i % 2 == 1)
                                {
                                    if ($i == 1)
                                        echo '<tr class="info">';  
                                    else
                                        echo '<tr>';
                                }
                                if ($i == 3)  
                                {
                                    echo '<tbody>';
                                    $bool = true;
                                }
                                if ($i <= 2)
                                    echo '<th>' . fgets($myfile) . '</th>';
                                else
                                    echo '<td>' . fgets($myfile) . '</td>';
                                if ($i % 2 == 0)
                                    echo '</tr>';
                                if ($i == 2)
                                    echo '</thead>';
                                
                            }
                            if ($bool)
                                echo '</tbody>';
                            echo '</table></div>';
                            fclose($myfile);


                            $file2 = $conf["source_path"] . '/' . $_POST["ass_name"] . '/' . $MSSV . '/' . $times . '/' . 'log.txt';
                            if (file_exists($file2))
                            {
                                echo '<div style="color: #ca5354;" >Thông tin biên dịch và lỗi chương trình</div><br>
                                <textarea class="form-control" id="exampleFormControlTextarea1" rows="3" style=" height: 300px;display: block; margin: 0 auto;"
                                >';
    
                                $myfile2 = fopen($file2, "r") or die("Unable to open file!");
                                $line = fgets($myfile2);
                                while ($line != "")
                                {
                                    echo $line;
                                    $line = fgets($myfile2);
                                }
                                echo '</textarea><br><br>';
                            }
                        }
                        
                        
                    }
                }
            }
            else if (isset($_GET['times']))
            {
                $conf = parse_ini_file($config_path . "/onlinejudge.conf");
                $MSSV = $_SESSION['mssv'];
                $times = $_GET['times'];
                $dir = $conf['source_path'] . '/' . $_GET['ass_name'] . '/' . $MSSV . '/' . $times . '/';
                if (file_exists($dir) == 0)
                {
                    echo '<div style="color: #ca5354" >Sinh viên không có lần nộp thứ ' . $times . '</div><br> ';
                }
                else
                {
                    echo '<h4 style="color: #00cc00;" >Kết quả lần nộp thứ ' . $times . '</h4><br>';
                    $file = $conf["source_path"] . '/' . $_GET["ass_name"] . '/' . $MSSV . '/' . $times . '/' . 'score.log';
                    if (file_exists($file) == 0)
                    {
                        echo '<div style="color: #ca5354" >Bài nộp mới nhất của sinh viên đang được chấm</div><br> ';
                    } 
                    else
                    {
                        $myfile = fopen($file, "r") or die("Unable to open file!");
                        echo '<div class="table-responsive">          
                        <table class="table table-bordered table-hover">';
                        $bool = false;
                        for($i= 1; !feof($myfile); $i++) 
                        {
                            if ($i == 1)
                                echo '<thead>';
                            if ($i % 2 == 1)
                            {
                                if ($i == 1)
                                    echo '<tr class="info">';  
                                else
                                    echo '<tr>';
                            }
                            if ($i == 3)  
                            {
                                echo '<tbody>';
                                $bool = true;
                            }
                            if ($i <= 2)
                                echo '<th>' . fgets($myfile) . '</th>';
                            else
                                echo '<td>' . fgets($myfile) . '</td>';
                            if ($i % 2 == 0)
                                echo '</tr>';
                            if ($i == 2)
                                echo '</thead>';
                            
                        }
                        if ($bool)
                            echo '</tbody>';
                        echo '</table></div>';
                        fclose($myfile);


                        $file2 = $conf["source_path"] . '/' . $_GET["ass_name"] . '/' . $MSSV . '/' . $times . '/' . 'log.txt';
                        if (file_exists($file2))
                        {
                            echo '<div style="color: #ca5354;" >Thông tin biên dịch và lỗi chương trình</div><br>
                            <textarea class="form-control" id="exampleFormControlTextarea1" rows="3" style=" height: 300px;display: block; margin: 0 auto;"
                            >';

                            $myfile2 = fopen($file2, "r") or die("Unable to open file!");
                            $line = fgets($myfile2);
                            while ($line != "")
                            {
                                echo $line;
                                $line = fgets($myfile2);
                            }
                            echo '</textarea><br><br>';
                        }
                    }
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