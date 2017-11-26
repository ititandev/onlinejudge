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
				</div>
			</div>
	</form> <br>
    </div>
    
    
    
    <?php 
        if(isset($_POST['up']) && isset($_FILES['fileUpload']))
        {
            $MSSV = $_POST['MSSV'];   
            
            if($_FILES['fileUpload']['error']>0)
                echo "Upload lỗi rồi!";
			else if ($_FILES['fileUpload']['type'] != 'application/zip')
				echo "Vui lòng nộp file .zip";
            else
            {
                for ($i = 0;; $i++) 
                {
                    $file = './upload/' . $MSSV . '_' . $i . '.zip';
                    //echo 'check file ' . $file . ': '. file_exists($file) . '<br>';
                    if (file_exists($file) == 0)
                    {
                        move_uploaded_file($_FILES['fileUpload']['tmp_name'],$file);
                        chmod($file, 0777);
                        break;
                    }
                }
				echo $MSSV . ' nộp bài thành công <br>';
                echo 'Dung lượng: ' . ((int)$_FILES['fileUpload']['size']/1024) .'KB';
            }
                
        }
     ?>
</body>
</html>