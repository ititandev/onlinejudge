<?php
session_start();
require 'db.php';
if ( $_SESSION['logged_in'] != 1  || $_SESSION['as_admin'] != 1) {
  $_SESSION['message'] = "Bạn phải đăng nhập admin trước khi sử dụng!";
  header("location: error.php");    
}
$ass_name = $_GET['ass_name'];
header('Content-Type: text/csv; charset=utf-8');
header('Content-Disposition: attachment; filename=' . $ass_name . '.csv');

$output = fopen('php://output', 'w');
fputcsv($output, array('MSSV', 'Score', 'Time', 'Submit times'), ';');
$times = 1;
$conf = parse_ini_file($config_path . "/onlinejudge.conf");
// $source_path = $conf['source_path'];
$source_path = "./Source";
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
    fputcsv($output, array($mssv, $score, $times, $date), ';');
}
    
?>
