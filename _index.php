<?php  
if(isset($_POST["btn_zip"]))  
{  
     $output = '';  
     if($_FILES['zip_file']['name'] != '')  
     {  
          $file_name = $_FILES['zip_file']['name'];  
          $array = explode(".", $file_name);  
          $name = $array[0];  
          $ext = $array[1];  
          if($ext == 'zip')  
          {  
               $path = 'upload/';  
               $location = $path . $file_name;  
               if(move_uploaded_file($_FILES['zip_file']['tmp_name'], $location))  
               {  
                    $zip = new ZipArchive;  
                    if($zip->open($location))  
                    {  
                         $zip->extractTo($path);  
                         $zip->close();  
                    }  
                    $files = scandir($path . $name);  
                    //$name is extract folder from zip file  
                    foreach($files as $file)  
                    {  
                         $file_ext = end(explode(".", $file));  
                         $allowed_ext = array('jpg', 'png');  
                         if(in_array($file_ext, $allowed_ext))  
                         {  
                              $new_name = md5(rand()).'.' . $file_ext;  
                              $output .= '<div class="col-md-6"><div style="padding:16px; border:1px solid #CCC;"><img src="upload/'.$new_name.'" width="170" height="240" /></div></div>';  
                              copy($path.$name.'/'.$file, $path . $new_name);  
                              unlink($path.$name.'/'.$file);  
                         }       
                    }  
                    unlink($location);  
                    rmdir($path . $name);  
               }  
          }  
     }  
}  
?>
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
	<br>
	<div class="container" style="width:500px;">
		<form enctype="multipart/form-data" method="post">
			<div class="row">
				<label for="name">MSSV <span class="req">*</span></label> <input class="txt" id="name" name="name" placeholder="1611985" required="" tabindex="1" type="text">
			</div>
			<div class="row">
				<label for="name">File zip <span class="req">*</span></label> <input class="txt" name="zip_file" type="file">
			</div><br>
			<div class="row">
				<div class="btnSubmit">
					<input class="btn btn-info" name="btn_zip" type="submit" value="Upload">
				</div>
			</div>
		</form><br>
		<?php  
		               if(isset($output))  
		               {  
		                    echo $output;  
		               }  
		               ?>
	</div><br>
</body>
</html>