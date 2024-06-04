import { FormType } from "@/types/FormType";
import { Product } from "@/types/Product";
import { User } from "@/types/User";
import { Bounce, toast } from "react-toastify";
import Button from "../Button";
import { BASE_URL } from "@/types/constants";
import { useEffect, useState } from "react";

interface ModifyFormProps {
  user: User;
  product: Product
  setFormType: React.Dispatch<React.SetStateAction<FormType>>;
}

const ModifyForm: React.FC<ModifyFormProps> = ({ user, product, setFormType }) => {
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

  const [productData, setProductData] = useState<Product>({id: 0, name: '', quantity: 0, price: 0})
  
  useEffect(() => {
    setProductData(product)
  }, [])

  const handleModifyProduct = () => {
    fetch(`${BASE_URL}/product/update?email=${user.email}&password=${user.password}&id=${productData.id}`, {
      method: 'PATCH',
      headers: {
        'Content-Type': 'application/json',
        'Access-Control-Allow-Origin': '*'
      },
      body: JSON.stringify({
        name: productData.name,
        quantity: productData.quantity,
        price: productData.price
      })
    }).then(response => {
      if (response.ok) {
        setFormType(FormType.NONE)
      } else {
        response.text().then(text => notify(text))
      }
    })
  }

  return (
    <div className="flex flex-col items-center justify-center">
      <p className="text-black font-bold text-2xl mb-2">Modify Product</p>
      <p className="text-black">Are you sure you want to modify this product?</p>
      <div className="space-y-3 mt-4 flex flex-col items-center">
        <input
          value={productData.name}
          onChange={(e) => {e.target.value.length !== 0 ? setProductData({ ...productData, name: e.target.value}) : null}}
          className='border w-60 border-gray-300 bg-white text-black h-10 px-4 pr-10 rounded-lg focus:outline-none'
        />
        <input
          value={productData.quantity}
          onChange={(e) => {/^\d+$/.test(e.target.value) ? setProductData({ ...productData, quantity: +e.target.value}) : null}}
          className='border w-60 border-gray-300 bg-white text-black h-10 px-4 pr-10 rounded-lg focus:outline-none'
        />
        <input
          value={productData.price}
          onChange={(e) => {/^\d+$/.test(e.target.value) ? setProductData({ ...productData, price: +e.target.value}) : null}}
          className='border w-60 border-gray-300 bg-white text-black h-10 px-4 pr-10 rounded-lg focus:outline-none'
        />
      </div>
      <div className="flex justify-center space-x-4 mt-5">
        <Button 
          label = "Modify"
          onClick = {() => handleModifyProduct()}
          width="5rem"
        />
        <Button 
          label = "Cancel"
          onClick = {() => setFormType(FormType.NONE)}
          width="5rem"
        />
      </div>
    </div>
  );
}

export default ModifyForm;