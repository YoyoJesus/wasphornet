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

document.addEventListener("DOMContentLoaded", function () {
    const socialFeed = document.getElementById("social-feed");
    const seeMoreButton = document.createElement("button");
    seeMoreButton.textContent = "See More";
    seeMoreButton.className = "btn btn-secondary mt-3";
    seeMoreButton.style.backgroundColor = "lightblue"; // Set light blue background
    seeMoreButton.style.color = "white"; // Set text color to white for better contrast
    seeMoreButton.style.display = "block"; // Make the button a block element
    seeMoreButton.style.margin = "0 auto"; // Center the button horizontally
    let currentIndex = 0;
    const postsPerPage = 4;
    let allPosts = [];

    // Function to render posts
    function renderPosts() {
        const nextPosts = allPosts.slice(currentIndex, currentIndex + postsPerPage);
        nextPosts.forEach(post => {
            const postElement = document.createElement("div");
            postElement.className = "col-md-6 mb-4";
            postElement.innerHTML = `
                <div class="interest-item">
                    <h3>${post.platform}</h3>
                    <p>${post.content}</p>
                    ${post.image ? `<img src="${post.image}" alt="Post Image" class="img-fluid mt-2">` : ""}
                    <p class="text-muted small">${post.date}</p>
                    ${post.link ? `<a href="${post.link}" target="_blank" class="btn btn-primary">View Post</a>` : ""}
                </div>
            `;
            socialFeed.appendChild(postElement);
        });
        currentIndex += postsPerPage;

        // Hide the button if no more posts to load
        if (currentIndex >= allPosts.length) {
            seeMoreButton.style.display = "none";
        }
    }

    // Function to fetch and render social media posts
    async function fetchSocialMediaPosts() {
        try {
            const response = await fetch('social-media-posts.json');
            if (!response.ok) {
                throw new Error('Failed to fetch social media posts');
            }
            allPosts = await response.json();

            // Sort posts by date (newest to oldest)
            allPosts.sort((a, b) => new Date(b.date) - new Date(a.date));

            // Render the initial set of posts
            renderPosts();

            // Add the "See More" button if there are more posts
            if (allPosts.length > postsPerPage) {
                socialFeed.appendChild(seeMoreButton);
            }
        } catch (error) {
            console.error('Error loading social media posts:', error);
        }
    }

    // Event listener for "See More" button
    seeMoreButton.addEventListener("click", renderPosts);

    fetchSocialMediaPosts();
});