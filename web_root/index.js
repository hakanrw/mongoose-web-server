async function fetchArch() {
  const archElement = document.getElementById('arch');

  try {
    const response = await fetch('/api/arch');

    if (!response.ok) {
      throw new Error(`HTTP error! Status: ${response.status}`);
    }

    archElement.textContent = await response.text();
  } catch (error) {
    console.error('Error fetching arch:', error);
    archElement.textContent = 'error';
  }

}

async function fetchSrv() {
  const osElement = document.getElementById('server');

  try {
    const response = await fetch('/api/server');

    if (!response.ok) {
      throw new Error(`HTTP error! Status: ${response.status}`);
    }

    osElement.textContent = await response.text();
  } catch (error) {
    console.error('Error fetching server:', error);
    osElement.textContent = 'error';
  }

}

async function fetchUsers() {
  const usersElement = document.getElementById('users');
  usersElement.textContent = "fetching users...";

  try {
    const response = await fetch('/api/user');

    if (!response.ok) {
      throw new Error(`HTTP error! Status: ${response.status}`);
    }

    usersElement.textContent = await response.text();
  } catch (error) {
    console.error('Error fetching users:', error);
    usersElement.textContent = 'error while fetching users';
  }
}

async function createUser() {
  const messageElement = document.getElementById('message');

  try {
    messageElement.textContent = '';
    const url = '/api/user';
    const requestData = {
       name: document.getElementById('name').value
    };

    const response = await fetch(url, {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json'
      },
      body: JSON.stringify(requestData)
    });

    if (!response.ok) {
      throw new Error(`HTTP error! Status: ${response.status}`);
    }

    messageElement.textContent = 'user created!';

    fetchUsers();
  }
  catch (error) {
        console.error('Error creating user:', error);
        messageElement.textContent = 'error while creating user';
  }
}
