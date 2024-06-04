using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Net.Http;
using System.Net.Http.Json;
using System.Threading.Tasks;
using TestCSharp;

class Program
{
    static HttpClient client = new HttpClient();

    static async Task Main(string[] args)
    {
        client.BaseAddress = new Uri("http://localhost:8080");

        Console.WriteLine("Get One");
        var responseGet = await client.GetAsync("api/shows/44");
        responseGet.EnsureSuccessStatusCode();
        var responseSpecatacolGet = await responseGet.Content.ReadFromJsonAsync<SpectacolDTOResponse>();
        Console.WriteLine(responseSpecatacolGet.ToString());
        
        Console.WriteLine("Get All");
        var responseGetAll = await client.GetAsync("api/shows");
        responseGetAll.EnsureSuccessStatusCode();
        var responseSpecatacolGetAll = await responseGetAll.Content.ReadFromJsonAsync<List<SpectacolDTOResponse>>();
        foreach (var spectacolDtoResponse in responseSpecatacolGetAll)
        {
            Console.WriteLine(spectacolDtoResponse);
        }
        
        Console.WriteLine("Post");
        var requestSpectacol = new SpectacolDTORequest("2024-04-09T19:08:40", "Sala Palatului", 100, 1);
        var response = await client.PostAsJsonAsync("api/shows", requestSpectacol);
        response.EnsureSuccessStatusCode();
        var responseSpectacol =  await response.Content.ReadFromJsonAsync<SpectacolDTOResponse>();
        Console.WriteLine(responseSpectacol.ToString());
        
        Console.WriteLine("Update");
        var requestSpectacolUpdate = new SpectacolDTORequest("2024-04-09T19:08:40", "Sala Mare", 99, 1);
        var responseUpdate = await client.PutAsJsonAsync("api/shows/1", requestSpectacolUpdate);
        responseUpdate.EnsureSuccessStatusCode();
        var responseSpectacolUpdate =  await responseUpdate.Content.ReadFromJsonAsync<SpectacolDTOResponse>();
        Console.WriteLine(responseSpectacolUpdate.ToString());

        Console.WriteLine("Delete");
        var responseDelete = await client.DeleteAsync("api/shows/1");
        responseDelete.EnsureSuccessStatusCode();
        Console.WriteLine(responseDelete.StatusCode);
        
    }
}

public class ResponseBody<T>
{
    public T Body { get; set; }
    public string Message { get; set; }
}
