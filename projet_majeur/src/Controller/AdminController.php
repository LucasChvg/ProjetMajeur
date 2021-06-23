<?php

namespace App\Controller;

use App\Entity\Data;
use Sensio\Bundle\FrameworkExtraBundle\Configuration\IsGranted;
use Symfony\Bundle\FrameworkBundle\Controller\AbstractController;
use Symfony\Component\HttpFoundation\Response;
use Symfony\Component\Routing\Annotation\Route;

class AdminController extends AbstractController
{
    /**
     * @Route("/admin", name="admin")
     * @IsGranted("ROLE_USER")
     */
    public function index(): Response
    {
        $data = $this->getDoctrine()->getRepository(Data::class)->findAll();



        return $this->render('admin/index.html.twig', [
            'data' => $data,
        ]);
    }
}
