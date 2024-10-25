function checkForm() {
   // Resetting previous validation state
   const inputs = document.querySelectorAll('input');
   inputs.forEach(input => input.classList.remove('error'));
   const formErrors = document.getElementById('formErrors');
   formErrors.innerHTML = '';

   let hasErrors = false;

   // Validating Full Name
   const fullName = document.getElementById('fullName').value.trim();
   if (fullName.length === 0) {
      addError('Missing full name.');
      hasErrors = true;
      document.getElementById('fullName').classList.add('error');
   }

   // Validating Email
   const email = document.getElementById('email').value.trim();
   const emailRegex = /^[a-zA-Z0-9._-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,5}$/;
   if (!emailRegex.test(email)) {
      addError('Invalid or missing email address.');
      hasErrors = true;
      document.getElementById('email').classList.add('error');
   }

   // Validating Password
   const password = document.getElementById('password').value;
   if (password.length < 10 || password.length > 20) {
      addError('Password must be between 10 and 20 characters.');
      hasErrors = true;
      document.getElementById('password').classList.add('error');
   } else {
      const lowercaseRegex = /[a-z]/;
      const uppercaseRegex = /[A-Z]/;
      const digitRegex = /[0-9]/;
      if (!lowercaseRegex.test(password)) {
         addError('Password must contain at least one lowercase character.');
         hasErrors = true;
         document.getElementById('password').classList.add('error');
      }
      if (!uppercaseRegex.test(password)) {
         addError('Password must contain at least one uppercase character.');
         hasErrors = true;
         document.getElementById('password').classList.add('error');
      }
      if (!digitRegex.test(password)) {
         addError('Password must contain at least one digit.');
         hasErrors = true;
         document.getElementById('password').classList.add('error');
      }
   }

   // Validating Confirm Password
   const confirmPassword = document.getElementById('confirmPassword').value;
   if (password !== confirmPassword) {
      addError('Password and confirmation password don\'t match.');
      hasErrors = true;
      document.getElementById('confirmPassword').classList.add('error');
   }

   // Displaying errors if any
   if (hasErrors) {
      formErrors.classList.remove('hide');
   } else {
      formErrors.classList.add('hide');
   }
}

document.getElementById("submit").addEventListener("click", function (event) {
   checkForm();
   event.preventDefault();
});
