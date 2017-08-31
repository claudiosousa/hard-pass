console.log('loaded extension')

const generatePasswordButton = document.querySelector("#generate-password-button");

generatePasswordButton.addEventListener("click", (e) => {
    browser.tabs.executeScript(null, { file: '/content_scripts/insert_password.js' });
});
