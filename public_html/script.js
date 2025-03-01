/* Reset some default styles */
// (Your existing styles here...)

const roles = [
    "Cybersecurity Enthusiast",
    "Hackathon Coordinator",
    "Researcher",
    "Hobbiest Web Developer",
    "Tech Enthusiast",
    "Student",
    "Battlebots Enthusiast",
    "Problem Solver",
    "All Around Nerd",
];

const typingText = document.querySelector(".typing-text");
const cursor = document.querySelector(".cursor");

let roleIndex = 0;
let charIndex = 0;
let isDeleting = false;

function typeEffect() {
    const currentRole = roles[roleIndex];
    
    if (isDeleting) {
        typingText.textContent = currentRole.substring(0, charIndex--);
    } else {
        typingText.textContent = currentRole.substring(0, charIndex++);
    }

    if (!isDeleting && charIndex === currentRole.length) {
        setTimeout(() => isDeleting = true, 1000); // Pause before deleting
    } else if (isDeleting && charIndex === 0) {
        isDeleting = false;
        roleIndex = (roleIndex + 1) % roles.length; // Move to the next role
    }

    setTimeout(typeEffect, isDeleting ? 50 : 100);
}

// Start typing effect when the page loads
document.addEventListener("DOMContentLoaded", typeEffect);


// Hamburger Menu toggle functionality
const hamburger = document.querySelector('.hamburger');
const menu = document.querySelector('.menu');

hamburger.addEventListener('click', () => {
    menu.classList.toggle('active');
});


// Matrix Rain (Hacker Mode) JavaScript
function createMatrixRain() {
    const rainContainer = document.createElement('div');
    rainContainer.classList.add('matrix-rain');
    document.body.appendChild(rainContainer);

    const characters = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789';
    const numColumns = Math.floor(window.innerWidth / 20);
    const numRows = Math.floor(window.innerHeight / 20);

    let columns = [];

    // Create the rain effect
    for (let i = 0; i < numColumns; i++) {
        columns[i] = 0;  // Start each column at the top

        let columnSpan = document.createElement('span');
        columnSpan.textContent = characters.charAt(Math.floor(Math.random() * characters.length));
        columnSpan.style.left = `${i * 20}px`;
        columnSpan.style.top = `${columns[i]}px`;
        rainContainer.appendChild(columnSpan);
    }

    function updateRain() {
        for (let i = 0; i < numColumns; i++) {
            const columnSpan = rainContainer.children[i];
            columns[i]++;

            if (columns[i] * 20 > window.innerHeight) {
                columns[i] = 0;
                columnSpan.textContent = characters.charAt(Math.floor(Math.random() * characters.length));
            }
            columnSpan.style.top = `${columns[i] * 20}px`;
        }
    }

    setInterval(updateRain, 50);
}

// Trigger Matrix Rain when Hacker Mode is toggled
const hackerModeButton = document.querySelector('.hacker-mode-button');
const body = document.body;

hackerModeButton.addEventListener('click', () => {
    body.classList.toggle('hacker-mode');
    const rainContainer = document.querySelector('.matrix-rain');
    
    // If hacker mode is activated and no rain exists, start it
    if (body.classList.contains('hacker-mode') && !rainContainer) {
        createMatrixRain();
    } else {
        // If hacker mode is deactivated, remove the rain effect
        if (rainContainer) {
            rainContainer.remove();
        }
    }
});
