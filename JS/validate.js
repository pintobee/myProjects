/* Original validate.js */
document.addEventListener("DOMContentLoaded", function () {
    // Add event listener to form submission
    document.getElementById('visitor-form').addEventListener('submit', function (event) {
        event.preventDefault(); // Prevent default form submission behavior

        // Validate form inputs
        if (validateForm()) {
            // If form is valid, submit the form
            this.submit();
        }
    });
});
// Function to validate the form
function validateForm() {
    // Get form elements
    let firstName = document.getElementById('first-name');
    let lastName = document.getElementById('last-name');
    let email = document.getElementById('email');
    let phone = document.getElementById('phone');
    let howFind = document.getElementById('how-find');

    // Validate first name
    if (firstName.value === '') {
        alert('Please enter your first name.');
        return false;
    }

    // Validate last name
    if (lastName.value === '') {
        alert('Please enter your last name.');
        return false;
    }

    // Validate email
    if (!validateEmail(email.value)) {
        alert('Please enter a valid email address.');
        return false;
    }

    // Validate phone
    if (!validatePhone(phone.value)) {
        alert('Please enter a valid phone number.');
        return false;
    }

    // Validate how did you find
    if (howFind.value === '') {
        alert('Please select how you found our page.');
        return false;
    }

    // If all validations pass, return true
    return true;
}

// Function to validate email
function validateEmail(email) {
    const re = /\S+@\S+\.\S+/;
    return re.test(email);
}

// Function to validate phone number
function validatePhone(phone) {
    const re = /^\d{10}$/;
    return re.test(phone);
}

// Event listener for form submission
document.getElementById('visitor-form').addEventListener('submit', function (event) {
    // Prevent default form submission
    event.preventDefault();

    // Validate the form
    if (validateForm()) {
        // If form is valid, show a success message
        document.getElementById('visitor-formContainer').style.display = 'none';
        document.getElementById('thank-you-message').style.display = 'block';
    }
});
