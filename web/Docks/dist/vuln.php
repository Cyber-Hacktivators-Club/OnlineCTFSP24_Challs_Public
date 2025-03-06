<?php
error_reporting(0);
session_start();

$flag = trim(file_get_contents("/flag.txt"));


// 1. strcmp bypass with unicode best fit vulnerability FOR PASSWROD  
$admin_user = "admin";

// Remove the problematic error_log that causes TypeError
if($_POST['username'] === "admin") {
    error_log("[-] Admin user not set correctly");
    die("Not so easy lol");
}

$result = @strcmp($admin_user, $_POST['username']); // Store result to avoid multiple calls
if ($result == 0) { // Use loose comparison for vulnerability
   error_log("[+] Authentication bypass successful");
    if(strtoupper($_POST['password']) == "PASSWORD123"){
        $_SESSION['auth'] = true;
        error_log("[+] Password bypass successful");
    } else {
        error_log("[-] Password bypass failed - password: " . $_POST['password']);
        die("Invalid password");
    }
} else {
    error_log("[-] Authentication failed");
    die("Invalid credentials");
}

// 2. $_REQUEST bypass
if (isset($_REQUEST['check']) && $_REQUEST['check'] == "1") {
    $_SESSION['request_bypass'] = true;
    error_log("[+] Request bypass successful");
} else {
    error_log("[-] Request bypass failed - check value: " . (isset($_REQUEST['check']) ? $_REQUEST['check'] : 'not set'));
}

// 3. extract() misuse with prefix
if (isset($_GET['var'])) {
    extract($_GET, EXTR_PREFIX_ALL, "flag");
    if (isset($flag_var) && $flag_var == true) {
        $_SESSION['extract_bypass'] = true;
        error_log("[+] Extract bypass successful");
    } else {
        error_log("[-] Extract bypass failed - var value: " . (isset($_GET['var']) ? $_GET['var'] : 'not set'));
    }
}

// 4. preg_match regex bypass
if (isset($_POST['desc']) && preg_match('/^secure_description$/', $_POST['desc'])) {
    $_SESSION['regex_bypass'] = true;
    error_log("[+] Regex bypass successful");
} else {
    error_log("[-] Regex bypass failed - desc value: " . (isset($_POST['desc']) ? $_POST['desc'] : 'not set'));
}

// 5. Base64 decode check bypass
if (isset($_POST['encoded'])) {
    $decoded = base64_decode($_POST['encoded'], true);
    if ($decoded !== false && $decoded === "solveIT") {
        $_SESSION['base64_bypass'] = true;
        error_log("[+] Base64 bypass successful");
    } else {
        error_log("[-] Base64 bypass failed - encoded value: " . (isset($_POST['encoded']) ? $_POST['encoded'] : 'not set'));
    }
}

// Log final status
$status = array(
    'auth' => !empty($_SESSION['auth']),
    'request_bypass' => !empty($_SESSION['request_bypass']),
    'extract_bypass' => !empty($_SESSION['extract_bypass']),
    'regex_bypass' => !empty($_SESSION['regex_bypass']),
    'base64_bypass' => !empty($_SESSION['base64_bypass'])
);
error_log("Current challenge status: " . json_encode($status));

// Check if all conditions met
if (!empty($_SESSION['auth']) && !empty($_SESSION['request_bypass']) && !empty($_SESSION['extract_bypass']) && !empty($_SESSION['regex_bypass']) && !empty($_SESSION['base64_bypass'])) {
    error_log("[+] All challenges completed successfully!");
    die("FLAG: $flag");
} else {
    error_log("[-] Not all challenges completed yet");
    die("You haven't solved all challenges yet!");
}
?>