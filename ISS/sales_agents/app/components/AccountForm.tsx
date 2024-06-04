'use client'
import { useState } from 'react';
import InputField from './InputField';
import Button from './Button';
import 'react-toastify/dist/ReactToastify.css';
import { Bounce, ToastContainer, toast } from 'react-toastify';
import { User } from '@/types/User';

interface AccountFormProps {
  setUser: React.Dispatch<React.SetStateAction<User | undefined>>
}

const AccountForm: React.FC<AccountFormProps> = ({ setUser }) => {
  const [inputEmail, setInputEmail] = useState<string>('')
  const [inputPassword, setInputPassword] = useState<string>('')
  const [inputConfirmPassword, setInputConfirmPassword] = useState<string>('')
  const [inputName, setInputName] = useState<string>('')
  const [newAccount, setNewAccount] = useState<boolean>(false)

  const notify = (error: string) => toast.error(error, {
    position: "top-right",
    autoClose: 5000,
    hideProgressBar: false,
    closeOnClick: true,
    pauseOnHover: true,
    draggable: true,
    progress: undefined,
    theme: "dark",
    transition: Bounce,
    });

  const handleSignInOrUpButton = () => {
    if (newAccount) {
      fetch(`http://localhost:8080/user/register`, {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json',
          'Access-Control-Allow-Origin': '*'
        },
        body: JSON.stringify({
          email: inputEmail,
          password: inputPassword,
          name: inputName,
          role: 'SALES_AGENT'
        })
      }).then(response => {
        if (response.ok) {
          return response.json()
        } else {
          response.text().then(text => notify(text))
          return
        }
      })
      .then(data => {
        setUser(data)
      })
    } 
    else {
      fetch(`http://localhost:8080/user/authorize?email=${inputEmail}&password=${inputPassword}`, {
        method: 'GET',
        headers: {
          'Content-Type': 'application/json',
          'Access-Control-Allow-Origin': '*'
        } 
      }).then(response => {
        if (response.ok) {
          return response.json()
        } else {
          response.text().then(text => notify(text))
          return
        }
      })
      .then(data => {
        setUser(data)
      })
    }
  }

  return (
    <div className='flex flex-col items-center space-y-4'>
      {newAccount && 
        <InputField
          placeholder="Name"
          input={inputName}
          setInput={setInputName}
        />
      }
      <InputField
        placeholder="Email"
        input={inputEmail}
        setInput={setInputEmail}
      />
      <InputField
        type="password"
        placeholder="Password"
        input={inputPassword}
        setInput={setInputPassword}
      />
      {newAccount && 
        <InputField
          type="password"
          placeholder="Repeat Password"
          input={inputConfirmPassword}
          setInput={setInputConfirmPassword}
        />
      }
      <Button
        label={newAccount ? 'Create Account' : 'Login'}
        width = '24rem'
        onClick={() => handleSignInOrUpButton()}
      />
      <div className="flex items-center">
        <input
          type="checkbox"
          className="form-checkbox h-5 w-5 text-indigo-600 transition duration-150 ease-in-out"
          checked={newAccount}
          onChange={() => setNewAccount(!newAccount)}
        />
        <p className="ml-2">New here?</p>
      </div>
    </div>
  )
};

export default AccountForm;