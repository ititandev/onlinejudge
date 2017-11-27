<!DOCTYPE html>
<html>
<head>
    <title>Hệ thống chấm điểm tự động</title>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/2.2.0/jquery.min.js">
    </script>
    <link href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/css/bootstrap.min.css" rel="stylesheet">
    <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/js/bootstrap.min.js">
    </script>
    <link href="styles.css" media="all" rel="stylesheet" type="text/css">
    <link href="http://www.aao.hcmut.edu.vn/image/data/khoa/logo.png" rel="icon">
</head>
<body>
    <!--<form action="" method="post" enctype="multipart/form-data" >
        <input type="text" name="MSSV" id="name" class="txt" tabindex="1" placeholder="1611985" required>
        <input type="file" name="fileUpload" value="">
        <input type="submit" name="up" value="Upload">
    </form>
    -->
    <br>
    <div class="container" style="width:500px;">
    <form action="" enctype="multipart/form-data" method="post">
			<div class="row">
				<label for="name">MSSV <span class="req">*</span></label> 
                <input class="txt" id="name" name="MSSV" placeholder="1611985" required="" tabindex="1" type="text">
			</div>
			<div class="row">
				<label for="name">File zip <span class="req">*</span></label> 
                <input class="txt" name="fileUpload" type="file">
			</div><br>
			<div class="row">
				<div class="btnSubmit">
					<input class="btn btn-info" name="up" type="submit" value="Upload">
                    <input class="btn btn-info" name="view" type="submit" value="Xem điểm">
				</div>
			</div>
            <?php
                  
                if (isset($_POST['view']))
                {
                    $MSSV = $_POST['MSSV']; 
                    for ($i = 1;; $i++)
                    {
                        $dir = './Source/' . $MSSV . '/' . $i . '/';
                        if (file_exists($dir) == 0)
                        {
                            break;
                        }
                    }
                    $i--;

                    echo '<br>';
                    echo '<div class="row" style=" font-size: 150%;">';
                    echo '<label for="name" style="color: #0066ff; width: 700px;" >' . 'Kết quả chấm điểm của sinh viên mã số ' . $MSSV . '</label> ';
                    echo '</div>';
                    
                    if ($i == 0)
                    {
                        echo '<div class="row" style=" font-size: 120%;"> <label for="name" style="color: #ca5354; width: 500px;" >Sinh viên chưa nộp bài lần nào</label></div> ';
                    }
                    else
                    {
                        $file = './Source/' . $MSSV . '/' . $i . '/score.log';
                        if (file_exists($file) == 0)
                            echo '<div class="row" style=" font-size: 120%;"> <label for="name" style="color: #ca5354; width: 500px;" >Bài nộp mới nhất của sinh viên đang được chấm</label></div> ';
                        else
                        {
                            echo '<div class="row" style=" font-size: 120%;"> <label for="name" style="color: #00cc00; width: 500px;" >' ;
                            $myfile = fopen($file, "r") or die("Unable to open file!");
                            while(!feof($myfile)) {
                            echo fgets($myfile).'<br>';
                            }
                            fclose($myfile);
                            echo '</label></div>';

                            //echo 
                        }
                    }
                }

                if(isset($_POST['up']) && isset($_FILES['fileUpload']))
                {
                    $MSSV = $_POST['MSSV']; 
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
	</form> <br>
    </div>
    
    
</body>
</html>