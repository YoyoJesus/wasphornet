<?php
// filepath: /users/kent/student/asternb1/public_html/guestbook.php

// File path to store entries
$filePath = __DIR__ . '/guestbook_entries.json';

// Ensure proper file permissions
if (!file_exists($filePath)) {
    file_put_contents($filePath, json_encode([])); // Create file if it doesn't exist
    chmod($filePath, 0666); // Set read/write permissions
}

// Handle form submission
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $name = htmlspecialchars($_POST['name']);
    $message = htmlspecialchars($_POST['message']);
    $timestamp = date('Y-m-d H:i:s');

    // Create a new entry
    $entry = [
        'timestamp' => $timestamp,
        'name' => $name,
        'message' => $message
    ];

    $entries = [];
    if (file_exists($filePath) && filesize($filePath) > 0) {
        $jsonData = @file_get_contents($filePath);
        $entries = json_decode($jsonData, true);
        if (!is_array($entries)) {
            $entries = [];
        }
    }

    $entries[] = $entry;

    // Save the updated entries back to the JSON file with locking
    $fileHandle = fopen($filePath, 'w');
    if (flock($fileHandle, LOCK_EX)) {
        fwrite($fileHandle, json_encode($entries, JSON_PRETTY_PRINT));
        flock($fileHandle, LOCK_UN);
    }
    fclose($fileHandle);
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Guestbook</title>
    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.5.2/css/bootstrap.min.css">
    <link rel="stylesheet" href="style.css">
</head>
<body>
    <header>
        <nav class="navbar navbar-expand-lg navbar-light navbar-custom">
            <div class="navbar-brand" href="#">
                <img class="largephoto" src="./assets/myAvatar.jpg" alt="Logo" style="width: 50px;">
                <span class="name">Austin Sternberg</span>
            </div>
            <button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarNav" aria-controls="navbarNav" aria-expanded="false" aria-label="Toggle navigation">
                <span class="navbar-toggler-icon"></span>
            </button>
            <div class="collapse navbar-collapse" id="navbarNav">
                <ul class="navbar-nav ml-auto">
                    <li class="nav-item"><a class="nav-link text-white" href="./">Home</a></li>
                    <li class="nav-item"><a class="nav-link text-white" href="about.html">About</a></li>
                    <li class="nav-item"><a class="nav-link text-white" href="projects.html">Projects</a></li>
                    <li class="nav-item"><a class="nav-link text-white" href="downloads.html">Downloads</a></li>
                    <li class="nav-item"><a class="nav-link text-white" href="resume.html">Resume</a></li>
                    <li class="nav-item"><a class="nav-link text-white" href="contact-1.html">Contact</a></li>
                    <li class="nav-item"><a class="nav-link text-white" href="guestbook.php">Guestbook</a></li>
                </ul>
            </div>
        </nav>
    </header>

    <div class="container mt-5 contact-form centered">
        <div class="content form-group">
            <h1>Guestbook</h1>
            <p>Leave a message below to share your thoughts!</p>

            <form method="POST" action="guestbook.php" class="centered">
                <label for="name">Name:</label>
                <input type="text" id="name" name="name" required>

                <label for="message">Message:</label>
                <textarea id="message" name="message" rows="4" required></textarea>

                <button type="submit" class="btn btn-primary">Submit</button>
            </form>
            <br/>
            <br/>
            <h2 class="mt-5">Messages</h2>
            <br/>
            <div class="guestbook-messages">
                <?php
                $entries = [];
                if (file_exists($filePath) && filesize($filePath) > 0) {
                    $fileHandle = fopen($filePath, "r");
                    if (flock($fileHandle, LOCK_SH)) {
                        $jsonData = fread($fileHandle, filesize($filePath));
                        flock($fileHandle, LOCK_UN);
                    }
                    fclose($fileHandle);

                    $entries = json_decode($jsonData, true);
                    if (!is_array($entries)) {
                        $entries = [];
                    }
                }

                if (!empty($entries)) {
                    foreach (array_reverse($entries) as $entry) {
                        echo '<p><strong>' . htmlspecialchars($entry['name']) . '</strong> (' . htmlspecialchars($entry['timestamp']) . '): ' . htmlspecialchars($entry['message']) . '</p>';
                    }
                } else {
                    echo '<p>No messages yet. Be the first to leave one!</p>';
                }
                ?>
            </div>
        </div>
    </div>

    <footer class="footer-custom text-center py-3">
        <div class="container">
            <p class="mb-0">2025 Austin Sternberg - Built with HTML, CSS, and PHP</p>
        </div>
    </footer>

    <script src="https://code.jquery.com/jquery-3.5.1.slim.min.js"></script>
    <script src="https://cdn.jsdelivr.net/npm/@popperjs/core@2.5.4/dist/umd/popper.min.js"></script>
    <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.5.2/js/bootstrap.min.js"></script>
</body>
</html>
