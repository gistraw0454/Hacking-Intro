<?php
// 업로드 디렉토리 설정
$target_dir = "uploads/";

// 파일이 제출되었는지 확인
if ($_SERVER["REQUEST_METHOD"] == "POST" && isset($_FILES["fileToUpload"])) {
    $target_file = $target_dir . basename($_FILES["fileToUpload"]["name"]);
    $uploadOk = 1;
    $file_extension = strtolower(pathinfo($target_file, PATHINFO_EXTENSION));

    // 허용된 PHP 파일 확장자만 업로드 가능하도록 검사 (여기서는 .php 만 허용)
    if ($file_extension != "php") {
        echo "PHP 파일만 업로드할 수 있습니다.";
        $uploadOk = 0;
    }

    // 파일을 업로드할 디렉토리 생성 (없으면)
    if (!file_exists($target_dir)) {
        mkdir($target_dir, 0777, true);
    }

    // 파일 업로드 검사
    if ($uploadOk == 1 && move_uploaded_file($_FILES["fileToUpload"]["tmp_name"], $target_file)) {
        // 파일 업로드 성공 시
        echo "파일 ". htmlspecialchars(basename($_FILES["fileToUpload"]["name"])). "이(가) 업로드 되었습니다.";
        echo "<br><br>";

        // 업로드된 PHP 파일 실행
        echo "실행 결과:<br>";
        echo "<iframe src='http://localhost/uploads/" . basename($_FILES["fileToUpload"]["name"]) . "' style='width: 100%; height: 400px; border: 1px solid #ccc;'></iframe>";
    } else {
        echo "파일 업로드에 실패했습니다.";
    }
}
?>
