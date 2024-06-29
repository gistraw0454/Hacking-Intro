<?php
$target_dir = "uploads/";
$target_file = $target_dir . basename($_FILES["fileToUpload"]["name"]);
$uploadOk = 1;
$imageFileType = strtolower(pathinfo($target_file, PATHINFO_EXTENSION));

// 파일이 제출되었는지 확인
if(isset($_POST["submit"])) {
    $check = getimagesize($_FILES["fileToUpload"]["tmp_name"]);
    if($check !== false) {
        echo "파일은 이미지 형식입니다. - " . $check["mime"] . ".";
        $uploadOk = 1;
    } else {
        echo "파일이 이미지가 아닙니다.";
        $uploadOk = 0;
    }
}

// 파일 업로드 처리
if ($uploadOk == 0) {
    echo "파일 업로드에 실패했습니다.";
} else {
    if (move_uploaded_file($_FILES["fileToUpload"]["tmp_name"], $target_file)) {
        echo "파일 ". htmlspecialchars(basename($_FILES["fileToUpload"]["name"])). "이(가) 업로드 되었습니다.";
        echo "<br>";
        echo "파일 경로: " . $target_file;
    } else {
        echo "파일 업로드에 실패했습니다.";
    }
}
?>
