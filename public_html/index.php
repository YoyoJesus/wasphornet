<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Home</title>
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

    <div class="container mt-5">
        <div class="content">
            <h1>Welcome!</h1>
            <div class="typing-container">
                <p class="intro">I am  <span id="typing-text"></span><span class="cursor">|</span></p>
            </div>
            <p>This website serves as a documentation of my work & a portfolio</p>
            
            <br>
            <h2>My Non-Programming Interests</h2>
            <div class="interests-grid">
                <div class="interest-item">
                    <h3>Dungeons & Dragons</h3>
                    <p>Worldbuilding, character creation, and immersive storytelling are some of my favorite things in D&D. Right now, I'm playing in a campaign inspired by <i>The Darkest Minds</i>.</p>
                </div>
                <div class="interest-item">
                    <h3>Gaming</h3>
                    <p>I enjoy both casual and competitive gaming. Some of my favorite titles include 
                        <b>
                            <ul>
                                <li>Bioshock</li>
                                <li>Baldur’s Gate 3</li>
                                <li>Halo</li>
                                <li>Hearts of Iron</li>
                                <li>Balatro</li>
                            </ul></b></p>
                </div>
                <div class="interest-item">
                    <h3>Music</h3>
                    <p>While my music taste can be vast, my friends describe my favorites as 'emo'. Some go-to artists: 
                        <b>
                            <ul>
                                <li>Twenty One Pilots</li>
                                <li>Green Day</li>
                                <li>Sabaton</li>
                                <li>Gorillaz</li>
                                <li>Holly Humberstone</li>
                            </ul></b></p>
                </div>
                <div class="interest-item">
                    <h3>Movies & TV</h3>
                    <p>My favorite genres are primarily sci-fi and fantasy. Some of my favorite movies and shows include: 
                        <b>
                            <ul>
                                <li>Doctor Who</li>
                                <li>Mr. Robot</li>
                                <li>Lord of the Rings</li>
                                <li>The Addams Family</li>
                                <li>The Martian</li>
                                <li>For All Mankind</li>
                                <li>Daredevil</li>
                            </ul>
                        </b></p>
                </div>
            </div>
        </div>
    </div>  

    <footer class="footer-custom text-center py-3">
        <div class="container">
            <p class="mb-0">2025 Austin Sternberg - Built with HTML, CSS, and JavaScript</p>
        </div>
    </footer>

    <script src="https://code.jquery.com/jquery-3.5.1.slim.min.js"></script>
    <script src="https://cdn.jsdelivr.net/npm/@popperjs/core@2.5.4/dist/umd/popper.min.js"></script>
    <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.5.2/js/bootstrap.min.js"></script>
    <script src="script.js"></script>
</body>
</html>
