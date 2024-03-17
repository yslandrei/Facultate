using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using csharp.domain;

namespace csharp.repository;


public interface IRepository<ID, E> where E : Entity<ID>
{
    E FindOne(ID id);

    List<E> FindAll();

    E Save(E entity);

 
    E Delete(ID id);
  
    E Update(E entity);
}