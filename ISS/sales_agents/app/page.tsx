'use client'
import { use, useEffect, useState } from "react"
import AccountForm from "./components/AccountForm"
import Button from "./components/Button"
import { ToastContainer } from "react-toastify"
import { ProductFilters, SortType } from "@/types/ProductFilters"
import { User } from "@/types/User"
import Slider from "@mui/material/Slider"
import RangeSlider from "./components/RangeSlider"
import ProductMenu from "./components/ProductMenu"

export default function Home() {
  const [user, setUser] = useState<User | undefined>(undefined)

  
  return (
    <main className="w-[100vw] h-[100vh] flex items-center flex-col justify-center">
      <p className='text-5xl font-bold mb-8'>Sales Agent Platform</p>
      <ToastContainer />
      {user === undefined && 
        <AccountForm 
          setUser={setUser}
        />
      } 
      {user !== undefined && 
        <div className="flex flex-col items-center">
          <div className="flex items-center mb-6 space-x-4">
            <p className="text-xl font-semibold">Welcome {user.name}!</p>
            <Button 
              label='Log out'
              width='6rem'
              onClick={() => setUser(undefined)}
            />
          </div>

          <ProductMenu
            user={user}
          />
          
        </div>
      }
    </main>
  )
}
