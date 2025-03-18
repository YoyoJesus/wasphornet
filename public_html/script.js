// Typing Effect Variables
const roles = [
    "Cybersecurity Enthusiast",
    "Hackathon Coordinator",
    "Researcher",
    "Hobbyist Web Developer",
    "Tech Enthusiast",
    "Student",
    "Battlebots Enthusiast",
    "Board Game Enthusiast",
    "D&D Player",
    "Problem Solver",
    "Science Fiction Fan",
    "All Around Nerd",
];

let roleIndex = 0;
let charIndex = 0;
let isDeleting = false;

window.getRoleWithArticle = function (role) {
    const article = /^[aeiou]/i.test(role) ? "an" : "a";
    return `${article} ${role}`;
}

function typeEffect() {
    const typingText = document.querySelector("#typing-text"); // Moved inside function to ensure it's available
    if (!typingText) {
        console.error("Error: Could not find #typing-text element.");
        return;
    }

    const currentRole = getRoleWithArticle(roles[roleIndex]);

    if (isDeleting) {
        typingText.textContent = currentRole.substring(0, charIndex--);
    } else {
        typingText.textContent = currentRole.substring(0, charIndex++);
    }

    if (!isDeleting && charIndex === currentRole.length) {
        setTimeout(() => (isDeleting = true), 1000);
    } else if (isDeleting && charIndex === 0) {
        isDeleting = false;
        roleIndex = (roleIndex + 1) % roles.length;
    }

    setTimeout(typeEffect, isDeleting ? 50 : 100);
}

document.addEventListener("DOMContentLoaded", () => {
    console.log("DOM fully loaded. Starting typeEffect...");
    typeEffect();

    // Hamburger Menu toggle functionality
    const hamburger = document.querySelector('.hamburger');
    const menu = document.querySelector('.menu');

    if (hamburger && menu) { // Null check to prevent errors
        hamburger.addEventListener('click', () => {
            menu.classList.toggle('active');
        });
    } else {
        console.warn("Hamburger menu elements not found.");
    }
});
