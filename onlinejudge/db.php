<?php
/* Database connection settings */
$host = 'localhost';
$user = 'root';
$pass = '';
$db = 'onlinejudge';
$mysqli = new mysqli($host,$user,$pass,$db) or die($mysqli->error);
$config_path = '../dsa/onlinejudge';