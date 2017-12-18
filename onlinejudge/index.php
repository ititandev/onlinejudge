<?php 
   /* Main page with two forms: sign up and log in */
   require 'db.php';
   session_start();
   if ( isset($_SESSION['logged_in']) && $_SESSION['logged_in'] == 1 ) {
    header("location: submit.php");    
    }
   ?>
<!DOCTYPE html>
<html>
   <head>
      <title>OnlineJudge</title>
      <?php include 'css/css.html'; ?>
      <link href="img/logo.png" rel="icon">
      <meta charshet="utf-8" />	
      <link href="img/logo.png" rel="icon"> 
   </head>
   <?php 
      if ($_SERVER['REQUEST_METHOD'] == 'POST') 
      {
          if (isset($_POST['login'])) { 
              require 'login.php';
          }
      }
      ?>
   <body>
        <div class="bg"> </div>
      <!--https://www.youtube.com/embed/MVpTk82P_xM?version=3&enablejsapi=1&html5=1&hd=1&wmode=opaque&showinfo=0&rel=0;;origin=http://60.hcmut.edu.vn;&controls=0 -->
      <div class="form" style=" z-index: 100; position:relative;">
         <div class="tab-content">
            <div id="login">
            	
               <h1>ĐĂNG NHẬP</h1>
               <h3>Hệ thống chấm điểm tự động CSE</h3>
               <form action="index.php" method="post" autocomplete="off">
                  <div class="field-wrap">
                     <label>
                     MSSV <span class="req">*</span>
                     </label>
                     <input type="text" required autocomplete="off" name="mssv"/>
                  </div>
                  <div class="field-wrap">
                     <label>
                     Mật khẩu<span class="req">*</span>
                     </label>
                     <input type="password" required autocomplete="off" name="password"/>
                  </div>
                  <p class="forgot"><a href="forgot.php">Quên mật khẩu?</a></p>
                  <button class="button button-block" name="login" />Đăng nhập</button>
               </form>
            </div>
            <div id="signup">   
            </div>
         </div>
         <!-- tab-content -->
      </div>
      <!-- /form -->
      <script src='http://cdnjs.cloudflare.com/ajax/libs/jquery/2.1.3/jquery.min.js'></script>
      <script src="js/index.js"></script>
      
   </body>
</html>