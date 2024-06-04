'use client'
import { FormType } from "@/types/FormType";
import { Product } from "@/types/Product";
import { RoleType, User } from "@/types/User";
import { useState } from "react";
import { MdDelete } from "react-icons/md";
import { MdEdit } from "react-icons/md";
import { MdShoppingCart } from "react-icons/md";
import { MdClose } from "react-icons/md";
import AddForm from "./forms/AddForm";
import DeleteForm from "./forms/DeleteForm";
import PlaceOrderForm from "./forms/PlaceOrderForm";
import ModifyForm from "./forms/ModifyForm";

interface ProductActionsProps {
  user: User;
  product: Product;
  setFormType: React.Dispatch<React.SetStateAction<FormType>>;
  setSelectedProduct: React.Dispatch<React.SetStateAction<undefined | Product>>;
}

const ProductActions: React.FC<ProductActionsProps> = ({ user, product, setFormType, setSelectedProduct }) => {

  return (
    <div className="flex space-x-2 justify-center items-center">
      {user.role === RoleType.ADMIN ? <>
        <MdEdit 
          onClick={() => {
            setFormType(FormType.MODIFY)
            setSelectedProduct(product)
          }}
          className="w-5 h-5 cursor-pointer"
        />
        <MdDelete 
          onClick={() => {
            setFormType(FormType.DELETE)
            setSelectedProduct(product)
          }}
          className="w-5 h-5 cursor-pointer"
        />
      </> :
        <MdShoppingCart 
          onClick={() => {
            setFormType(FormType.PLACE_ORDER)
            setSelectedProduct(product)
          }}
          className="w-5 h-5 cursor-pointer"
        />
      }
    </div>
  );
}

export default ProductActions;