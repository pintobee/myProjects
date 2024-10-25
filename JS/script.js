document.addEventListener("DOMContentLoaded", function () {
    // Get all menu links
    const menuLinks = document.querySelectorAll('.tabs a');

    // Get all sections
    const sections = document.querySelectorAll('section');

    // Hide all sections except the first one
    for (let i = 1; i < sections.length; i++) {
        sections[i].style.display = 'none';
    }

    // Add click event listener to each menu link
    menuLinks.forEach(function (menuLink) {
        menuLink.addEventListener('click', function (event) {
            event.preventDefault(); // Prevent default link behavior

            // Get the target section id from href attribute
            const targetId = this.getAttribute('href').substring(1);

            // Hide all sections
            sections.forEach(function (section) {
                section.style.display = 'none';
            });

            // Show the target section
            document.getElementById(targetId).style.display = 'block';
        });
    });

    // Initialize form validation for the contact form
    initValidation("visitor-form", "thank-you-message");
});

// Function to initialize form validation
function initValidation(formId, successId) {
    const form = document.getElementById(formId);
    const successMessage = document.getElementById(successId);

    form.addEventListener("submit", function (event) {
        event.preventDefault(); // Prevent default form submission

        // Perform form validation
        if (validateForm(form)) {
            // Hide the form
            form.style.display = "none";
            // Show the "Thank you" message
            successMessage.style.display = "block";
        }
    });
}

// Function to validate the form
function validateForm(form) {
    let isValid = true;

    // Validate each input field
    const inputs = form.querySelectorAll('input, select');
    inputs.forEach(function (input) {
        if (!input.checkValidity()) {
            isValid = false;
            // Display error message
            const errorMessage = input.nextElementSibling;
            errorMessage.textContent = input.validationMessage;
            errorMessage.style.display = "block";
        } else {
            // Hide error message if input is valid
            const errorMessage = input.nextElementSibling;
            errorMessage.textContent = "";
            errorMessage.style.display = "none";
        }
    });

    return isValid;
}

// Toggle theme function
function toggleTheme() {
    var newThemeLink = document.querySelector('link[href="newstyle.css"]');
    if (newThemeLink.disabled) {
        newThemeLink.disabled = false;
    } else {
        newThemeLink.disabled = true;
    }
}

document.getElementById('toggleButton').addEventListener('click', toggleTheme);
