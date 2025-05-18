<?php
if($_SERVER["REQUEST_METHOD"] == "POST") {
    $username = $_POST['username'] ?? '';
    $password = $_POST['password'] ?? '';
    
    // Temel validasyon
    if(empty($username) || empty($password)) {
        header("Location: login.html?error=empty_fields");
        exit();
    }
    
    // E-posta format kontrolü
    if(!filter_var($username, FILTER_VALIDATE_EMAIL) || 
       !preg_match('/^[a-zA-Z][a-zA-Z0-9]{10}@sakarya\.edu\.tr$/', $username)) {
        header("Location: login.html?error=invalid_email");
        exit();
    }
    
    // Şifre kontrolü (kullanıcı adının @ öncesi kısmı)
    $usernamePart = explode('@', $username)[0];
    if($password !== $usernamePart) {
        header("Location: login.html?error=invalid_password");
        exit();
    }
    
    // Başarılı giriş
    echo "<!DOCTYPE html>
    <html lang='tr'>
    <head>
        <meta charset='UTF-8'>
        <meta name='viewport' content='width=device-width, initial-scale=1.0'>
        <title>Hoşgeldiniz</title>
        <link href='https://cdn.jsdelivr.net/npm/bootstrap@5.3.0/dist/css/bootstrap.min.css' rel='stylesheet'>
    </head>
    <body>
        <div class='container mt-5'>
            <div class='alert alert-success text-center'>
                <h4>Hoşgeldiniz $usernamePart</h4>
                <p>Giriş işlemi başarılı!</p>
                <a href='login.html' class='btn btn-primary'>Çıkış Yap</a>
            </div>
        </div>
    </body>
    </html>";
} else {
    header("Location: login.html");
    exit();
}
?>