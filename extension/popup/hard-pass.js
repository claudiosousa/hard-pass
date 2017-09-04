browser.tabs.executeScript(null, { file: '/content_scripts/psl.min.js' });

const generatePasswordButton = document.querySelector("#generate-password-button");

generatePasswordButton.addEventListener("click", (e) => {
    browser.tabs.executeScript(null, { file: '/content_scripts/insert_password.js' });
});
