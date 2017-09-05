function findPasswordInput() {
    return document.querySelector('input[type="password"]');
}

function insertPassword(password) {
    const passwordInput = findPasswordInput()
    if (passwordInput) {
        passwordInput.value = password
    }
}
browser.runtime.onMessage.addListener(insertPassword);
